/* -*- c++ -*- */
/* 
 * Copyright 2021 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "selector_ff_impl.h"

#define SUMCOUNT 400000
#define THROTTLE 0.2

//#include <algorithm>

namespace gr {
  namespace mymod {

    selector_ff::sptr
    selector_ff::make()
    {
      return gnuradio::get_initial_sptr
        (new selector_ff_impl());
    }

    /*
     * The private constructor
     */
    selector_ff_impl::selector_ff_impl()
      : gr::sync_block("selector_ff",
              gr::io_signature::make(1, 5, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))),
      d_sum_count(0),
      d_sum0(0),
      d_sum1(0),
      d_sum2(0),
      d_sum3(0),
      d_sum4(0),
      d_index(0)
    {}

    /*
     * Our virtual destructor.
     */
    selector_ff_impl::~selector_ff_impl()
    {
    }

    int
    selector_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in0 = (const float *) input_items[0];
      const float *in1 = (const float *) input_items[1];
      const float *in2 = (const float *) input_items[2];
      const float *in3 = (const float *) input_items[3];
      const float *in4 = (const float *) input_items[4];
      float *out = (float *) output_items[0];    

        int noi = noutput_items;
        int max_index = -1;

        if(noi == 1)
        {
            d_sum0 += in0[0];
            d_sum1 += in1[0];
            d_sum2 += in2[0];
            d_sum3 += in3[0];
            d_sum4 += in4[0];
            d_sum_count++;

            if (d_sum_count == SUMCOUNT)
            {

              int index_temp = 0;
              int sum_max = d_sum0;
              int sum_list[5] = {d_sum0, d_sum1, d_sum2, d_sum3, d_sum4};
              for(int i = 1; i < 5; i++)
              {
                if((sum_list[i] > SUMCOUNT*THROTTLE ? sum_list[i] : 0) > sum_max)
                {
                  sum_max = sum_list[i];
                  index_temp = i;
                }
              }
              d_index = index_temp;

              d_sum_count = 0;
              d_sum0 = 0;
              d_sum1 = 0;
              d_sum2 = 0;
              d_sum3 = 0;
              d_sum4 = 0;
            }
        }
        else
        {
          for (int i = 0; i < noi - 1;)
          {
            d_sum0 += in0[i];
            d_sum1 += in1[i];
            d_sum2 += in2[i];
            d_sum3 += in3[i];
            d_sum4 += in4[i];

            d_sum_count++;
            i += 2;

            if (d_sum_count == SUMCOUNT)
            {

              //printf("%f\n", (d_sum2/100000));
              //out[0] = d_sum2/100000;

              int index_temp = 0;
              int sum_max = d_sum0;
              int sum_list[5] = {d_sum0, d_sum1, d_sum2, d_sum3, d_sum4};
              for(int i = 1; i < 5; i++)
              {
                if((sum_list[i] > SUMCOUNT*THROTTLE ? sum_list[i] : 0) > sum_max)
                {
                  sum_max = sum_list[i];
                  index_temp = i;
                }
              }
              d_index = index_temp;

              d_sum_count = 0;
              d_sum0 = 0;
              d_sum1 = 0;
              d_sum2 = 0;
              d_sum3 = 0;
              d_sum4 = 0;

              printf("%d \n", d_index);
            }

          }
        }
        //printf("%d \n", max_index);
        out[0] = d_index;
        


      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mymod */
} /* namespace gr */

