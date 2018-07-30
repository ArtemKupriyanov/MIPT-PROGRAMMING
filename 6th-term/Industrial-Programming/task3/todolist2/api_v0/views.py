from django.shortcuts import render

from rest_framework import viewsets, generics
from .serializers import *


class TasksViewSet(viewsets.ModelViewSet):
    
    queryset = Task.objects.filter(task_done=False).order_by("-pub_date")
    
    def get_serializer_class(self):
        return TaskPreviewSerializer

class TasksDoneView(generics.UpdateAPIView):
    queryset = Task.objects.filter(task_done=False).order_by("-pub_date")
    model = Task
    serializer_class = TaskPreviewSerializer
