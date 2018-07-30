import React, {Component} from 'react';
import {deleteTaskSignal} from './App.js';

class Task extends Component {
    constructor(props) {
        super(props)
        this.deleteTask = this.deleteTask.bind(this)
    }
    
    deleteTask(event) {
        var form = new FormData();
        form.append("id", this.props.item.id);
        form.append("task_text", this.props.item.text);
        form.append("task_done", true);
        fetch("http://localhost:8000/api/v0/task/" + this.props.item.id, {
              method: "DELETE",
              body: form
              });
    }
    
    render() {
        return (
                <div className="App">
                <p>{this.props.item.task_text}
                    <form type>
                        <input type="checkbox" onChange={this.deleteTask} value={this.props.item.task_done}>
                        </input>
                    </form>
                </p>
                </div>
                );
    }
}

export default Task;
