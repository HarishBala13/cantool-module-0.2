import { ChangeDetectorRef, Component, inject, OnDestroy, OnInit } from '@angular/core';
import { ElectronService } from '../../services/electron.service';
import { IpcRendererEvent } from 'electron';

@Component({
  selector: 'app-logs',
  standalone: true,
  imports: [],
  templateUrl: './logs.component.html',
  styleUrl: './logs.component.css'
})
export class LogsComponent implements OnInit, OnDestroy {

  logs: string[] = [];

  private electronService = inject(ElectronService);
  private cdr = inject(ChangeDetectorRef);

  ngOnInit(): void {

    console.log('Initializing Logs Component');

    this.electronService.on('update-logs', (event, logMessages) => {
      console.log(logMessages);
      this.logs.push(logMessages);
      this.cdr.detectChanges();
    });

  }

  clearLogs(): void {
    this.electronService.send('clear-logs');
    this.logs = [];
  }

  ngOnDestroy(): void {
    this.electronService.removeListener('update-logs', this.updateLogsListener);
  }

  private updateLogsListener = (event: IpcRendererEvent, logMessages: string[]) => {
    this.logs = logMessages;
  };

  // ngOnInit(): void {

  //   this.cdr.detectChanges();

  //   this.electronService.on('update-logs', (event, logs) => {
  //     console.log(logs)
  //     const logContainer = document.getElementById('logContainer');
  //     logContainer!.innerHTML = '';
  //     logs.forEach((log: string | null) => {
  //       const logEntry = document.createElement('div');
  //       logEntry.textContent = log;
  //       logContainer!.appendChild(logEntry);
  //     });
  //   });

  // }

  // clearLogs() {
  //   this.electronService.send('clear-logs');
  // }



  // window.electron.on('new-log', (event, logMessage) => {
  //     console.log(logMessage)
  //     const logContainer = document.getElementById('logContainer');
  //     const logEntry = document.createElement('div');
  //     logEntry.textContent = logMessage;
  //     console.log(logEntry)
  //     logContainer.appendChild(logEntry);
  // });




}
