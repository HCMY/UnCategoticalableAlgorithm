# -*- coding: utf-8 -*-
"""
Created on Thu May 25 18:31:30 2017

@author: Stu.zhouyc
"""

import pandas as pd

data = pd.read_csv('information.csv',encoding='utf-8')
print(data)
data.to_csv('infor_frame.csv',index=False)