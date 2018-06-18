from django.shortcuts import render

# Create your views here.

from django.shortcuts import render_to_response
from django.http import Http404, HttpResponse, HttpResponseRedirect
from searchengine.web_search import google

def search(request):

	if request.POST:
		return render_to_response('search.html', {'result': google(request.POST['term'], 10)})
	#return HttpResponseRedirect("/")
	else:
		return render_to_response('search.html')