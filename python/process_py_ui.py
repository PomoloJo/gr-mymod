#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2021 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

# -*- coding: utf-8 -*-

from gnuradio import gr
import pmt

from PyQt4.QtCore import QRect, Qt, QSize, pyqtSignal
from PyQt4.QtGui import *
import sys
from PIL import Image, ImageDraw
from PIL.ImageQt import ImageQt

import threading
from Queue import Queue


q_list = []
for i in range(19):
    q_list.append(Queue())

flag_keep_running = True

class MyWidget(QMainWindow):
    
    sig_arfcn_0 = pyqtSignal(tuple, int)
    sig_arfcn_1 = pyqtSignal(tuple, int)
    sig_arfcn_2 = pyqtSignal(tuple, int)
    sig_arfcn_3 = pyqtSignal(tuple, int)
    sig_arfcn_4 = pyqtSignal(tuple, int)
    sig_arfcn_5 = pyqtSignal(tuple, int)
    sig_arfcn_6 = pyqtSignal(tuple, int)
    sig_arfcn_7 = pyqtSignal(tuple, int)
    sig_arfcn_8 = pyqtSignal(tuple, int)
    sig_arfcn_9 = pyqtSignal(tuple, int)
    sig_arfcn_10 = pyqtSignal(tuple, int)
    sig_arfcn_11 = pyqtSignal(tuple, int)
    sig_arfcn_12 = pyqtSignal(tuple, int)
    sig_arfcn_13 = pyqtSignal(tuple, int)
    sig_arfcn_14 = pyqtSignal(tuple, int)
    sig_arfcn_15 = pyqtSignal(tuple, int)
    sig_arfcn_16 = pyqtSignal(tuple, int)
    sig_arfcn_17 = pyqtSignal(tuple, int)
    sig_arfcn_18 = pyqtSignal(tuple, int)


    
    def __init__(self):
        super(MyWidget, self).__init__()
        self.setObjectName("MainWindow")
        self.resize(1600, 800)
        #self.setMinimumSize(QSize(1600, 800))
        #self.setMaximumSize(QSize(1600, 800))
        self.setWindowTitle('railway_data')
        
        self.setupUi()


    def setupUi(self):
        self.tabWidget = QTabWidget(self)
        self.tabWidget.setGeometry(QRect(0, 0, 1600, 800))
        self.tabWidget.setObjectName("tabWidget")
        
        self.tab_arfcn_0 = QWidget(self)
        self.tab_arfcn_0.setObjectName("tab_arfcn_0")
        self.tabWidget.addTab(self.tab_arfcn_0, "")
        self.tab_arfcn_1 = QWidget(self)
        self.tab_arfcn_1.setObjectName("tab_arfcn_1")
        self.tabWidget.addTab(self.tab_arfcn_1, "")
        self.tab_arfcn_2 = QWidget(self)
        self.tab_arfcn_2.setObjectName("tab_arfcn_2")
        self.tabWidget.addTab(self.tab_arfcn_2, "")
        self.tab_arfcn_3 = QWidget(self)
        self.tab_arfcn_3.setObjectName("tab_arfcn_3")
        self.tabWidget.addTab(self.tab_arfcn_3, "")
        self.tab_arfcn_4 = QWidget(self)
        self.tab_arfcn_4.setObjectName("tab_arfcn_4")
        self.tabWidget.addTab(self.tab_arfcn_4, "")
        self.tab_arfcn_5 = QWidget(self)
        self.tab_arfcn_5.setObjectName("tab_arfcn_5")
        self.tabWidget.addTab(self.tab_arfcn_5, "")
        self.tab_arfcn_6 = QWidget(self)
        self.tab_arfcn_6.setObjectName("tab_arfcn_6")
        self.tabWidget.addTab(self.tab_arfcn_6, "")
        self.tab_arfcn_7 = QWidget(self)
        self.tab_arfcn_7.setObjectName("tab_arfcn_7")
        self.tabWidget.addTab(self.tab_arfcn_7, "")
        self.tab_arfcn_8 = QWidget(self)
        self.tab_arfcn_8.setObjectName("tab_arfcn_8")
        self.tabWidget.addTab(self.tab_arfcn_8, "")
        self.tab_arfcn_9 = QWidget(self)
        self.tab_arfcn_9.setObjectName("tab_arfcn_9")
        self.tabWidget.addTab(self.tab_arfcn_9, "")
        self.tab_arfcn_10 = QWidget(self)
        self.tab_arfcn_10.setObjectName("tab_arfcn_10")
        self.tabWidget.addTab(self.tab_arfcn_10, "")
        self.tab_arfcn_11 = QWidget(self)
        self.tab_arfcn_11.setObjectName("tab_arfcn_11")
        self.tabWidget.addTab(self.tab_arfcn_11, "")
        self.tab_arfcn_12 = QWidget(self)
        self.tab_arfcn_12.setObjectName("tab_arfcn_12")
        self.tabWidget.addTab(self.tab_arfcn_12, "")
        self.tab_arfcn_13 = QWidget(self)
        self.tab_arfcn_13.setObjectName("tab_arfcn_13")
        self.tabWidget.addTab(self.tab_arfcn_13, "")
        self.tab_arfcn_14 = QWidget(self)
        self.tab_arfcn_14.setObjectName("tab_arfcn_14")
        self.tabWidget.addTab(self.tab_arfcn_14, "")
        self.tab_arfcn_15 = QWidget(self)
        self.tab_arfcn_15.setObjectName("tab_arfcn_15")
        self.tabWidget.addTab(self.tab_arfcn_15, "")
        self.tab_arfcn_16 = QWidget(self)
        self.tab_arfcn_16.setObjectName("tab_arfcn_16")
        self.tabWidget.addTab(self.tab_arfcn_16, "")
        self.tab_arfcn_17 = QWidget(self)
        self.tab_arfcn_17.setObjectName("tab_arfcn_17")
        self.tabWidget.addTab(self.tab_arfcn_17, "")
        self.tab_arfcn_18 = QWidget(self)
        self.tab_arfcn_18.setObjectName("tab_arfcn_18")
        self.tabWidget.addTab(self.tab_arfcn_18, "")
        
        
        self.text_browser_size = QRect(0, 0, 1600, 780)
        self.textBrowser_arfcn_0 = QTextBrowser(self.tab_arfcn_0)
        self.textBrowser_arfcn_0.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_0.setObjectName("textBrowser_arfcn_0")
        self.textBrowser_arfcn_1 = QTextBrowser(self.tab_arfcn_1)
        self.textBrowser_arfcn_1.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_1.setObjectName("textBrowser_arfcn_1")
        self.textBrowser_arfcn_2 = QTextBrowser(self.tab_arfcn_2)
        self.textBrowser_arfcn_2.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_2.setObjectName("textBrowser_arfcn_2")
        self.textBrowser_arfcn_3 = QTextBrowser(self.tab_arfcn_3)
        self.textBrowser_arfcn_3.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_3.setObjectName("textBrowser_arfcn_3")
        self.textBrowser_arfcn_4 = QTextBrowser(self.tab_arfcn_4)
        self.textBrowser_arfcn_4.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_4.setObjectName("textBrowser_arfcn_4")
        self.textBrowser_arfcn_5 = QTextBrowser(self.tab_arfcn_5)
        self.textBrowser_arfcn_5.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_5.setObjectName("textBrowser_arfcn_5")
        self.textBrowser_arfcn_6 = QTextBrowser(self.tab_arfcn_6)
        self.textBrowser_arfcn_6.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_6.setObjectName("textBrowser_arfcn_6")
        self.textBrowser_arfcn_7 = QTextBrowser(self.tab_arfcn_7)
        self.textBrowser_arfcn_7.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_7.setObjectName("textBrowser_arfcn_7")
        self.textBrowser_arfcn_8 = QTextBrowser(self.tab_arfcn_8)
        self.textBrowser_arfcn_8.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_8.setObjectName("textBrowser_arfcn_8")
        self.textBrowser_arfcn_9 = QTextBrowser(self.tab_arfcn_9)
        self.textBrowser_arfcn_9.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_9.setObjectName("textBrowser_arfcn_9")
        self.textBrowser_arfcn_10 = QTextBrowser(self.tab_arfcn_10)
        self.textBrowser_arfcn_10.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_10.setObjectName("textBrowser_arfcn_10")
        self.textBrowser_arfcn_11 = QTextBrowser(self.tab_arfcn_11)
        self.textBrowser_arfcn_11.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_11.setObjectName("textBrowser_arfcn_11")
        self.textBrowser_arfcn_12 = QTextBrowser(self.tab_arfcn_12)
        self.textBrowser_arfcn_12.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_12.setObjectName("textBrowser_arfcn_12")
        self.textBrowser_arfcn_13 = QTextBrowser(self.tab_arfcn_13)
        self.textBrowser_arfcn_13.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_13.setObjectName("textBrowser_arfcn_13")
        self.textBrowser_arfcn_14 = QTextBrowser(self.tab_arfcn_14)
        self.textBrowser_arfcn_14.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_14.setObjectName("textBrowser_arfcn_14")
        self.textBrowser_arfcn_15 = QTextBrowser(self.tab_arfcn_15)
        self.textBrowser_arfcn_15.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_15.setObjectName("textBrowser_arfcn_15")
        self.textBrowser_arfcn_16 = QTextBrowser(self.tab_arfcn_16)
        self.textBrowser_arfcn_16.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_16.setObjectName("textBrowser_arfcn_16")
        self.textBrowser_arfcn_17 = QTextBrowser(self.tab_arfcn_17)
        self.textBrowser_arfcn_17.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_17.setObjectName("textBrowser_arfcn_17")
        self.textBrowser_arfcn_18 = QTextBrowser(self.tab_arfcn_18)
        self.textBrowser_arfcn_18.setGeometry(self.text_browser_size)
        self.textBrowser_arfcn_18.setObjectName("textBrowser_arfcn_18")


        self.textBrowser_list = [   
            self.textBrowser_arfcn_0,
            self.textBrowser_arfcn_1,
            self.textBrowser_arfcn_2,
            self.textBrowser_arfcn_3,
            self.textBrowser_arfcn_4,
            self.textBrowser_arfcn_5,
            self.textBrowser_arfcn_6,
            self.textBrowser_arfcn_7,
            self.textBrowser_arfcn_8,
            self.textBrowser_arfcn_9,
            self.textBrowser_arfcn_10,
            self.textBrowser_arfcn_11,
            self.textBrowser_arfcn_12,
            self.textBrowser_arfcn_13,
            self.textBrowser_arfcn_14,
            self.textBrowser_arfcn_15,
            self.textBrowser_arfcn_16,
            self.textBrowser_arfcn_17,
            self.textBrowser_arfcn_18 ]
                
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_0), "arfcn_0")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_1), "arfcn_1")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_2), "arfcn_2")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_3), "arfcn_3")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_4), "arfcn_4")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_5), "arfcn_5")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_6), "arfcn_6")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_7), "arfcn_7")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_8), "arfcn_8")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_9), "arfcn_9")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_10), "arfcn_10")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_11), "arfcn_11")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_12), "arfcn_12")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_13), "arfcn_13")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_14), "arfcn_14")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_15), "arfcn_15")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_16), "arfcn_16")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_17), "arfcn_17")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_arfcn_18), "arfcn_18")
        
                                  
        
        self.tabWidget.setCurrentIndex(0)

        global flag_keep_running
        flag_keep_running = True

        self.sig_list = [   self.sig_arfcn_0, self.sig_arfcn_1, self.sig_arfcn_2, self.sig_arfcn_3, 
                            self.sig_arfcn_4, self.sig_arfcn_5, self.sig_arfcn_6, self.sig_arfcn_7,
                            self.sig_arfcn_8, self.sig_arfcn_9, self.sig_arfcn_10, self.sig_arfcn_11, 
                            self.sig_arfcn_12, self.sig_arfcn_13, self.sig_arfcn_14, self.sig_arfcn_15,
                            self.sig_arfcn_16, self.sig_arfcn_17, self.sig_arfcn_18]
        
        for i in range(19):
            self.sig_list[i].connect(self.draw)

        # self.count_list = []
        # for i in range(19):
        #     self.count_list.append([(0, 1) for j in range(40)])

        self.func_recv_list = []
        for i in range(19):
            self.func_recv_list.append(self.funcRecv(i))

        t_list = []
        for i in range(19):
            t_list.append(threading.Thread(target=self.func_recv_list[i]))
        for i in range(19):
            t_list[i].setDaemon(True)  # 守护线程，当主线程结束时子线程随之结束
            t_list[i].start()

    def funcRecv(self, i):
        def recv():
            global q_list
            while True:
                while flag_keep_running:
                    recv_data = q_list[i].get()
                    self.sig_list[i].emit(recv_data, i)
        return recv


    def draw(self, recv_data, c):
        text = ''
        color_num = ''
        j = 0
        data_len = len(recv_data)
        for i in range(data_len):
            if (0 < i < data_len - 3):
                if(recv_data[i] == 16) and (recv_data[i + 1] == 16):
                    j+=1
            if i == 16 + j:
                if recv_data[i] in (241,3,4,5,6,7):
                    color_num = ' {:02x}'.format(recv_data[i])
                    color_num = '<span style=\" color: #ff0000;\">%s</span>' % color_num
                    text += color_num
            else:
                text += ' {:02x}'.format(recv_data[i])
        self.textBrowser_list[c].append(text)
        self.textBrowser_list[c].append(' ')


    def keepRunning(self):
        global flag_keep_running
        if flag_keep_running:
            flag_keep_running = False
        else:
            flag_keep_running = True


def show():
    app = QApplication(sys.argv)
    win = MyWidget()
    win.show()
    sys.exit(app.exec_())


class process_py_ui(gr.basic_block):
    """
    docstring for block process_py_ui
    """
    def __init__(self):
        gr.basic_block.__init__(self,
            name="process_py_ui",
            in_sig=None,
            out_sig=None)

        for i in range(19):
            self.message_port_register_in(pmt.intern('arfcn_{}'.format(i)))

        self.func_handle_msg_list = []

        for i in range(19):
            self.func_handle_msg_list.append(self.funcHandleMsg(i))

        for i in range(19):
            self.set_msg_handler(pmt.intern('arfcn_{}'.format(i)), self.func_handle_msg_list[i])

        t = threading.Thread(target=show)
        t.setDaemon(True)  # 守护线程，当主线程结束时子线程随之结束
        t.start()

    # 工厂函数
    def funcHandleMsg(self, i):
        def handleMsg(msg):
            global q_list
            global flag_keep_running
            if flag_keep_running:
                msg = pmt.cdr(msg)
                data = pmt.u8vector_elements(msg)
                q_list[i].put(data)
        return handleMsg


