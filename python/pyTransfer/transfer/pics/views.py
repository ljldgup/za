
import os,sys

from django.shortcuts import render
sys.path.append("..")
from transfer import settings


# Create your views here.

def home(request):

	return render(request, 'template/listDirs.html', {'dirs' : os.listdir(settings.STATICFILES_DIRS[0])})

def getPics(request, path):
	rst = {}
	rst['pics'] = os.listdir(settings.STATICFILES_DIRS[0] + '/' + path)
	rst['path'] = path
	return render(request, 'template/listPics.html', rst)
