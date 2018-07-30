from django.db import models


# Class for tasks in TODO List.
class Task(models.Model):
    task_text = models.CharField("text", max_length=200)
    pub_date = models.DateTimeField("date published")
    task_done = models.BooleanField("done_flag", default=False)

    def __str__(self):
        return self.task_text
