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

#pragma GCC diagnostic error "-std=c++11"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "data_extract_impl.h"

#include <algorithm>


namespace gr {
  namespace mymod {

    data_extract::sptr
    data_extract::make(int cs_mode, int link_flag, int arfcn)
    {
      return gnuradio::get_initial_sptr
        (new data_extract_impl(cs_mode, link_flag, arfcn));
    }

    /*
     * The private constructor
     */
    data_extract_impl::data_extract_impl(int cs_mode, int link_flag, int arfcn)
      : gr::block("data_extract",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
        d_csmode(cs_mode), // it can be const
        d_link_flag(link_flag), // can be const
        d_arfcn(arfcn)
    {
        message_port_register_in(pmt::mp("in")); 
        set_msg_handler(pmt::mp("in"), boost::bind(&data_extract_impl::extract, this, _1));
        message_port_register_out(pmt::mp("out"));
    }


    data_extract_impl::~data_extract_impl()
    {
    }



    void
    data_extract_impl::extract(pmt::pmt_t block_in)
    {

        pmt::pmt_t block_without_header = pmt::cdr(block_in);
        uint8_t * block_in_int8 = (uint8_t *)pmt::blob_data(block_without_header);

        std::vector<uint8_t> data_in;

        if(d_csmode == 1)
            data_in.assign(&block_in_int8[0], &block_in_int8[23]);
        else if(d_csmode == 2)
            data_in.assign(&block_in_int8[0], &block_in_int8[33]);
        else
          return;


        int ttl = 10;

        int switch_flag = -1;
        switch_flag = (block_in_int8[1]) >> 1;

        for (int i = 0; i < 32; i++)
        {
          if(!d_data_stack_list[i].empty())
            d_ttl_list[i]++;
        }

        switch (switch_flag)
        {
        case 0: d_data_stack_list[0].push_back(data_in); d_ttl_list[0] = 0; break;
        case 1: d_data_stack_list[1].push_back(data_in); d_ttl_list[1] = 0; break;
        case 2: d_data_stack_list[2].push_back(data_in); d_ttl_list[2] = 0; break;
        case 3: d_data_stack_list[3].push_back(data_in); d_ttl_list[3] = 0; break;
        case 4: d_data_stack_list[4].push_back(data_in); d_ttl_list[4] = 0; break;
        case 5: d_data_stack_list[5].push_back(data_in); d_ttl_list[5] = 0; break;
        case 6: d_data_stack_list[6].push_back(data_in); d_ttl_list[6] = 0; break;
        case 7: d_data_stack_list[7].push_back(data_in); d_ttl_list[7] = 0; break;
        case 8: d_data_stack_list[8].push_back(data_in); d_ttl_list[8] = 0; break;
        case 9: d_data_stack_list[9].push_back(data_in); d_ttl_list[9] = 0; break;
        case 10: d_data_stack_list[10].push_back(data_in); d_ttl_list[10] = 0; break;
        case 11: d_data_stack_list[11].push_back(data_in); d_ttl_list[11] = 0; break;
        case 12: d_data_stack_list[12].push_back(data_in); d_ttl_list[12] = 0; break;
        case 13: d_data_stack_list[13].push_back(data_in); d_ttl_list[13] = 0; break;
        case 14: d_data_stack_list[14].push_back(data_in); d_ttl_list[14] = 0; break;
        case 15: d_data_stack_list[15].push_back(data_in); d_ttl_list[15] = 0; break;
        case 16: d_data_stack_list[16].push_back(data_in); d_ttl_list[16] = 0; break;
        case 17: d_data_stack_list[17].push_back(data_in); d_ttl_list[17] = 0; break;
        case 18: d_data_stack_list[18].push_back(data_in); d_ttl_list[18] = 0; break;
        case 19: d_data_stack_list[19].push_back(data_in); d_ttl_list[19] = 0; break;
        case 20: d_data_stack_list[20].push_back(data_in); d_ttl_list[20] = 0; break;
        case 21: d_data_stack_list[21].push_back(data_in); d_ttl_list[21] = 0; break;
        case 22: d_data_stack_list[22].push_back(data_in); d_ttl_list[22] = 0; break;
        case 23: d_data_stack_list[23].push_back(data_in); d_ttl_list[23] = 0; break;
        case 24: d_data_stack_list[24].push_back(data_in); d_ttl_list[24] = 0; break;
        case 25: d_data_stack_list[25].push_back(data_in); d_ttl_list[25] = 0; break;
        case 26: d_data_stack_list[26].push_back(data_in); d_ttl_list[26] = 0; break;
        case 27: d_data_stack_list[27].push_back(data_in); d_ttl_list[27] = 0; break;
        case 28: d_data_stack_list[28].push_back(data_in); d_ttl_list[28] = 0; break;
        case 29: d_data_stack_list[29].push_back(data_in); d_ttl_list[29] = 0; break;
        case 30: d_data_stack_list[30].push_back(data_in); d_ttl_list[30] = 0; break;
        case 31: d_data_stack_list[31].push_back(data_in); d_ttl_list[31] = 0; break;
        default:
            break;
        }

        for(int j = 0; j < 32; j++)
        {
            if(d_ttl_list[j] == ttl)
            {
                int data_size = d_data_stack_list[j].size();
                int data_len_by_cs = 13 + d_csmode * 10;

                uint8_t *data_send = new uint8_t[data_size * data_len_by_cs];
                sort( d_data_stack_list[j].begin(),
                      d_data_stack_list[j].end(), 
                      [](std::vector<uint8_t> vector_sort_a, std::vector<uint8_t> vector_sort_b)
                      {return vector_sort_a[2] < vector_sort_b[2];}
                    );  // , bind(&data_extract_impl::sortCompare, this, _1, _2)

                int temp_3bytes = -1;

                int index = 0;
                int data_number = 0;
                int data_idx[100] = {99};
                int data_count[100] = {0};
                for(int i = data_size-1 ; i >= 0; i--)
                {
                    if(temp_3bytes == (d_data_stack_list[j][i][2] >> 1))
                        continue;
                    else
                    {
                        temp_3bytes = (d_data_stack_list[j][i][2] >> 1);

                        // delete the head, and judge from the third bytes
                        int count = 2;
                        for(int m = 2; m < data_len_by_cs - 4; m++)  // original: m < data_len_by_cs, -4 is to avoid out of bounds
                        {
                            if(d_data_stack_list[j][i][m] % 2)
                              break;
                            count++;
                        }

                        if((d_data_stack_list[j][i][1] & 1) and (d_link_flag & 1))
                            count += 4;
                        data_idx[data_number] = i;
                        data_count[data_number] = count;
                        data_number += 1;
                    }
                }
                for (int i = 0; i < data_number; i++)
                {
                    int n = data_idx[data_number - i - 1];
                    int count = data_count[data_number - i - 1];
                    d_data_stack_list[j][n].erase(d_data_stack_list[j][n].begin(), d_data_stack_list[j][n].begin() + count + 1);
                    memcpy(data_send + index, &d_data_stack_list[j][n][0], (data_len_by_cs - 1 - count));
                    index += (data_len_by_cs - 1 - count);
                }
              

                // data send in this function
                extractAndSend(index, data_send);

                d_data_stack_list[j].clear();
                delete []data_send;

                d_data_stack_list[j].clear();
                d_ttl_list[j] = 0;
            }
        }
    }


    // extract data from 1002 to 1003
    void data_extract_impl::extractAndSend(int index, uint8_t *data_send)
    {
        int flag_1002 = -1;
        int flag_1003 = -1;
        int flag_10[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        if(data_send[0] == 16 and data_send[1] == 2)
            flag_1002 = 0;
        int count_10 = 0;
        for(int i = 1; i < index - 1; i++)
        {
            if(flag_1002 < 0)
            {
                if(data_send[i] == 16 and data_send[i - 1] != 16 and data_send[i + 1] == 2)
                  flag_1002 = i;
            }
            else if(data_send[i] == 16 and data_send[i - 1] == 16)
            {
              count_10 += 1;
              flag_10[count_10 - 1] = i;
              i++;

            }
            else if(data_send[i] == 16 and data_send[i - 1] != 16 and data_send[i + 1] == 3)
            {

                flag_1003 = i + 1;
                int valid_length = flag_1003 - flag_1002 + 1 - count_10;
                if(((data_send[flag_1002 + 2] << 8) + data_send[flag_1002 + 3]) == valid_length - 6)
                {
                  uint8_t address_len = data_send[flag_1002 + 5];
                  uint8_t valid_bytes = data_send[flag_1002 + 16];
                  int add_10 = 0;
                  for(int n = 0;n < count_10; n++)
                  {
                    if(flag_10[n] <= flag_1002 + 16)
                      add_10 += 1;

                  }
                  valid_bytes = data_send[flag_1002 + 16 + add_10];
                    if(address_len == 4 and (valid_bytes == 5 or valid_bytes == 6 or valid_bytes == 7 or valid_bytes == 241)
                      or address_len == 6)
                    {
                        data_send[flag_1003 + 1] = d_arfcn;
                        uint8_t *real_data_send = new uint8_t[valid_length + 1 + count_10];
                        memcpy(real_data_send, data_send + flag_1002, valid_length + 1 + count_10);
                        pmt::pmt_t msg_binary_blob = pmt::make_blob(data_send + flag_1002, valid_length + 1 + count_10);
                        pmt::pmt_t data_out = pmt::cons(pmt::PMT_NIL, msg_binary_blob);
                        message_port_pub(pmt::mp("out"), data_out);
                        delete []real_data_send;
                        //printf("\n");
                    }
                }
                flag_1002 = -1;
                flag_1003 = -1;
                count_10 = 0;
            }
        }
    }
    


  } /* namespace mymod */
} /* namespace gr */

