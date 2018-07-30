from django.shortcuts import render, redirect, get_object_or_404, render_to_response
from django.views.decorators.http import require_POST

from django.http import HttpResponse
from django.template import RequestContext, loader
from todotasks.models import Task
from todotasks.forms import TodoForm
import datetime


def index(request):
    tasks_list = Task.objects.filter(task_done=False).order_by("-pub_date")
    form = TodoForm()
    context = {
                "tasks_list": tasks_list,
                "form": form
              }
    return render(request, "todotasks/index.html", context)


def detail(request, task_id):
    task = get_object_or_404(Task, id=task_id)
    return render_to_response('todotasks/detail.html', {"task": task})


def delite(request, task_id):
    task = Task.objects.filter(id=task_id).update(task_done=True)
    return redirect('index')


@require_POST
def addTodo(request):
    form = TodoForm(request.POST)
    print (request.POST['text'])
    if form.is_valid():
        new_task = Task(task_text=request.POST['text'], pub_date=datetime.datetime.now())
        new_task.save()
    return redirect('index')
