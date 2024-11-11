import { Injectable } from '@angular/core';
import { ipcRenderer, IpcRendererEvent } from 'electron';

@Injectable({
  providedIn: 'root'
})
export class ElectronService {

  public ipc: typeof ipcRenderer | undefined;

  constructor() {
    this.ipc = (window as any).electron ? (window as any).electron.ipcRenderer : undefined;
    if (!this.ipc)
      console.warn('Electron\'s IPC was not loaded');
  }

  send(channel: any, ...args: any[]): void {
    if (this.ipc) {
      this.ipc.send(channel, ...args);
    }
  }

  on(channel: any, listener: (event: IpcRendererEvent, ...args: any[]) => void): void {
    if (this.ipc) {
      this.ipc.on(channel, listener);
    }
  }

  removeListener(channel: string, listener: (event: IpcRendererEvent, ...args: any[]) => void): void {
    if (this.ipc) {
      this.ipc.removeListener(channel, listener);
    }
  }
}
