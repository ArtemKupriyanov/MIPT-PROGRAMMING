from django.conf.urls import url

from todotasks import views

urlpatterns = [
               url(r'^$', views.index, name='index'),
               url(r'^add', views.addTodo, name='add'),
               url(r'^todotasks/(?P<task_id>\d+)/$', views.detail, name='detail'),
               url(r'^del/(?P<task_id>\d+)$', views.delite, name='delite')
              ]
