from rest_framework.routers import DefaultRouter
from django.conf.urls import url, include
from .views import *


router = DefaultRouter()
router.register(r'tasks', TasksViewSet)

urlpatterns = [
    url(r'^', include(router.urls)),
    url(r'^taskdone/(?P<id>\d+)/$', TasksDoneView.as_view(), name="task done"),
]
