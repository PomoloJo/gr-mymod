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
#define THROTTLE 0.3

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
              gr::io_signature::make(1, 19, sizeof(float)),
              gr::io_signature::make(0,0,0)),
      d_sum_count(0),
      d_sum0(0),
      d_sum1(0),
      d_sum2(0),
      d_sum3(0),
      d_sum4(0),
      d_sum5(0),
      d_sum6(0),
      d_sum7(0),
      d_sum8(0),
      d_sum9(0),
      d_sum10(0),
      d_sum11(0),
      d_sum12(0),
      d_sum13(0),
      d_sum14(0),
      d_sum15(0),
      d_sum16(0),
      d_sum17(0),
      d_sum18(0),
      d_index(0)
    {
        message_port_register_out(pmt::mp("out"));
    }

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
      const float *in5 = (const float *) input_items[5];
      const float *in6 = (const float *) input_items[6];
      const float *in7 = (const float *) input_items[7];
      const float *in8 = (const float *) input_items[8];
      const float *in9 = (const float *) input_items[9];
      const float *in10 = (const float *) input_items[10];
      const float *in11 = (const float *) input_items[11];
      const float *in12 = (const float *) input_items[12];
      const float *in13 = (const float *) input_items[13];
      const float *in14 = (const float *) input_items[14];
      const float *in15 = (const float *) input_items[15];
      const float *in16 = (const float *) input_items[16];
      const float *in17 = (const float *) input_items[17];
      const float *in18 = (const float *) input_items[18];
      //float *out = (float *) output_items[0];    

        int max_index = -1;

        if(noutput_items == 1)
        {
            d_sum0 += in0[0];
            d_sum1 += in1[0];
            d_sum2 += in2[0];
            d_sum3 += in3[0];
            d_sum4 += in4[0];
            d_sum5 += in5[0];
            d_sum6 += in6[0];
            d_sum7 += in7[0];
            d_sum8 += in8[0];
            d_sum9 += in9[0];
            d_sum10 += in10[0];
            d_sum11 += in11[0];
            d_sum12 += in12[0];
            d_sum13 += in13[0];
            d_sum14 += in14[0];
            d_sum15 += in15[0];
            d_sum16 += in16[0];
            d_sum17 += in17[0];
            d_sum18 += in18[0];
            d_sum_count++;

            if (d_sum_count == SUMCOUNT)
            {

              int index_temp = 0;
              int sum_max = d_sum0;
              int sum_list[20] = 
              {0, d_sum0, d_sum1, d_sum2, d_sum3, d_sum4, d_sum5, d_sum6, d_sum7, d_sum8, d_sum9,
                d_sum10, d_sum11, d_sum12, d_sum13, d_sum14, d_sum15, d_sum16, d_sum17, d_sum18};
              for(int i = 1; i < 20; i++)
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
              d_sum5 = 0;
              d_sum6 = 0;
              d_sum7 = 0;
              d_sum8 = 0;
              d_sum9 = 0;
              d_sum10 = 0;
              d_sum11 = 0;
              d_sum12 = 0;
              d_sum13 = 0;
              d_sum14 = 0;
              d_sum15 = 0;
              d_sum16 = 0;
              d_sum17 = 0;
              d_sum18 = 0;

              //out[0] = d_index;
              //printf("%d \n", d_index);
              pmt::pmt_t msg_binary_blob = pmt::make_blob(&d_index, 1);
              pmt::pmt_t burst_out = pmt::cons(pmt::PMT_NIL, msg_binary_blob);
              message_port_pub(pmt::mp("out"), burst_out);
            }
        }
        else
        {
          for (int i = 0; i < noutput_items - 1;)
          {
            d_sum0 += in0[i];
            d_sum1 += in1[i];
            d_sum2 += in2[i];
            d_sum3 += in3[i];
            d_sum4 += in4[i];
            d_sum5 += in5[i];
            d_sum6 += in6[i];
            d_sum7 += in7[i];
            d_sum8 += in8[i];
            d_sum9 += in9[i];
            d_sum10 += in10[i];
            d_sum11 += in11[i];
            d_sum12 += in12[i];
            d_sum13 += in13[i];
            d_sum14 += in14[i];
            d_sum15 += in15[i];
            d_sum16 += in16[i];
            d_sum17 += in17[i];
            d_sum18 += in18[i];

            d_sum_count++;
            i += 2;

            if (d_sum_count == SUMCOUNT)
            {

              //printf("%f\n", (d_sum2/100000));
              //out[0] = d_sum2/100000;

              int index_temp = 0;
              int sum_max = d_sum0;
              int sum_list[20] = 
              {0, d_sum0, d_sum1, d_sum2, d_sum3, d_sum4, d_sum5, d_sum6, d_sum7, d_sum8, d_sum9,
                d_sum10, d_sum11, d_sum12, d_sum13, d_sum14, d_sum15, d_sum16, d_sum17, d_sum18};
              for(int i = 1; i < 20; i++)
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
              d_sum5 = 0;
              d_sum6 = 0;
              d_sum7 = 0;
              d_sum8 = 0;
              d_sum9 = 0;
              d_sum10 = 0;
              d_sum11 = 0;
              d_sum12 = 0;
              d_sum13 = 0;
              d_sum14 = 0;
              d_sum15 = 0;
              d_sum16 = 0;
              d_sum17 = 0;
              d_sum18 = 0;

              //out[0] = d_index;
              pmt::pmt_t msg_binary_blob = pmt::make_blob(&d_index, 1);
              pmt::pmt_t burst_out = pmt::cons(pmt::PMT_NIL, msg_binary_blob);
              message_port_pub(pmt::mp("out"), burst_out);
              //printf("%d \n", d_index);
            }

          }
        }
        // printf("%d \n", d_index);
        // out[0] = d_index;
        


      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mymod */
} /* namespace gr */

