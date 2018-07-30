import React, { Component } from 'react';
import Task from './Task.js';
import logo from './logo.svg';
import './App.css';

class App extends Component {
    constructor(props) {
        super(props)
        this.state = {
            error: null,
            new_task: "",
            tasks: []
        }
        this.taskFetch = this.taskFetch.bind(this);
    }
    
    taskFetch() {
        fetch("http://localhost:8000/api/v0/tasks", {method:'GET', content: 'application/json'})
        .then(ans => ans.json())
        .then((ans) => {this.setState({tasks: ans});}
        )
    }
    
    componentDidMount() {
        this.taskFetch();
    }
    
    TaskCreate(event) {
        console.log(this.state.new_task)
        let form = new FormData();
        form.append("task_text", this.state.new_task);
        form.append("task_done", false);
        fetch("http://localhost:8000/api/v0/tasks", {method:'POST', body: form})
    }
    
    TaskChange(event) {
        this.setState({new_task: event.target.value});
    }
    
  render() {
    return (
      <div className="App">
            <form>
                <input type="text" onChange={this.TaskChange.bind(this)}>
            
                </input>
                <button onSubmit={this.TaskCreate.bind(this)}>
                    Добавить
                </button>
            </form>
            <div>
                {this.state.tasks.map((i) => <Task item={i}/>)}
            </div>
      </div>
    );
  }
}

export default App;
