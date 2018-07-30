from rest_framework import serializers
from tasks.models import Task

class TaskPreviewSerializer(serializers.ModelSerializer):
    class Meta:
        model = Task
        fields = [
                  'id',
                  'pub_date',
                  'task_text',
                  'task_done',
                  ]
