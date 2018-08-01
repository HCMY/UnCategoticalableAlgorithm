# coding:utf8

import random

from http import cookiejar
import http
import urllib
import requests
import re
from bs4 import BeautifulSoup

from PIL import Image
import pytesseract


capture_head ={#'Accept':'*/*',
               'Accept-Encoding':'gzip, deflate',
               #'Accept-Language':'zh-CN,zh;q=0.9',
               #'Connection':'keep-alive',
               #'Cookie':'language=1; \
               #        BIGipServercache.neea.edu.cn_pool=564185098.39455.0000; \
               #        Hm_lvt_dc1d69ab90346d48ee02f18510292577=\
               #       1519718456,1519718544,1519718583; \
                #       Hm_lpvt_dc1d69ab90346d48ee02f18510292577=1519718583',
               #'DNT':'1',
               #'Host':'cache.neea.edu.cn',
               'Referer':'http://cet.neea.edu.cn/cet',
               'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) \
                               Chrome/64.0.3282.140 Safari/537.36'}

query_url = 'http://cache.neea.edu.cn/cet/query'

query_header = {
        'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
        'Accept-Encoding':'gzip, deflate',
        'Accept-Language':'zh-CN,zh;q=0.9',
        'Cache-Control':'max-age=0',
        'Content-Length':'75',
        'Content-Type':'application/x-www-form-urlencoded',
        #'Cookie:language=1; BIGipServercache.neea.edu.cn_pool=564185098.39455.0000; Hm_lvt_dc1d69ab90346d48ee02f18510292577=1519718456,1519718544,1519718583; Hm_lpvt_dc1d69ab90346d48ee02f18510292577=1519720817',
        'DNT':'1',
        'Host':'cache.neea.edu.cn',
        'Origin':'http://cet.neea.edu.cn',
        'Proxy-Connection':'keep-alive',
        'Referer':'http://cet.neea.edu.cn/cet',
        'Upgrade-Insecure-Requests':'1',
        'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36'
        }

cookie = http.cookiejar.CookieJar()
process = urllib.request.HTTPCookieProcessor(cookie)
opener = urllib.request.build_opener(process)


access_exam_stu_name = '周建国'


def create_id():
    start = 510081172202201
    end__ = 510081172202315
    numbers = []
    while(start<=end__):
        for i in range(40):
            numbers.append(start)
            start += 1
        start +=100
        start -= 40
    
    numbers = [str(x) for x in numbers]
    return numbers
    


def get_img_url(access_exam_stu_id):
    cap_url = 'http://cache.neea.edu.cn/Imgs.do?c=CET&ik=%s&t=%s'%(access_exam_stu_id, random.random())
    request = urllib.request.Request(cap_url,headers = capture_head)
    response = opener.open(request)
    content = response.read().decode('utf-8')
    pattern =  re.compile(r'http.*?\.png|jpg')
    img_url = re.findall(pattern, content)[0]
        
    return img_url
    
def save_img(img_url):
    urllib.request.urlretrieve(img_url,'cap.png')
        
   
def query(access_exam_id, verify_code):
    v = verify_code
    form_data = {'data':'CET6_172_DANGCI,%s,%s'%(access_exam_id, access_exam_stu_name),'v':v}
    form_data = urllib.parse.urlencode(form_data).encode(encoding='UTF8')
    request = urllib.request.Request(url=query_url, data=form_data, headers=query_header)
    response = opener.open(request)
    status = response.getcode()
    content = BeautifulSoup(response.read().decode('utf-8'))
    if content.find('您查询的结果为空'):
        return 1
    elif content.find('抱歉，验证码错误'):
        return 2    
    elif status is 200:
        print (access_exam_stu_name, access_exam_id, content)
        return 200
    
def extract_capture_words(access_exam_stu_id):
        captupe_url = get_img_url(access_exam_stu_id)
        save_img(captupe_url)
        #picture = self.opener.open(captupe_url).read()
        #local = open(self.img_name,'wb')
        #local.write(picture)
        #local.close()
        im = Image.open('cap.png')
        check_code = pytesseract.image_to_string(im)
        #check_code = input('输入验证码: ')
        #check_code = str(check_code)
        print("check code= ",check_code)
        return check_code
    

if __name__=="__main__":
    id_list = create_id()
    student_index = 0
    samples = len(id_list)
    
    while(student_index<samples):
        student_index+=1
        stu_id = id_list[student_index]
        print('student number:',stu_id)
        #try:
        status = extract_capture_words(stu_id)
        print("status=",status)
        #except:
        #    continue
        COUT = 0
        while(COUT<=10 and status is 2):
            COUT+=1
            try:
                status = extract_capture_words(stu_id)
                print("status yzx=",status)
            except:
                continue
        if status is 1:
           continue
        elif status is 200:
            break
        student_index+=1
    
            
            
    
        
        

        
        
        