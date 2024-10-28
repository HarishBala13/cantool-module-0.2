import { ChangeDetectorRef, Component, inject, OnInit } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { ElectronService } from './services/electron.service';
import { FooterComponent } from './shared/footer/footer.component';
import { SidebarComponent } from "./shared/sidebar/sidebar.component";
import { SignalDetailsComponent } from './shared/signal-details/signal-details.component';
import { LogsComponent } from './shared/logs/logs.component';
import { ConfigureFileComponent } from './shared/configure-file/configure-file.component';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, ConfigureFileComponent, FooterComponent, SidebarComponent, SignalDetailsComponent, LogsComponent],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})

export class AppComponent implements OnInit {
  title = 'angular-app';
  isFormVisible: boolean = false;
  isLogsWindowVisible: boolean = false;

  private electronService = inject(ElectronService);
  private cdr = inject(ChangeDetectorRef);

  ngOnInit(): void {
    this.electronService.on('open-form', () => {
      this.isFormVisible = true;
      this.cdr.detectChanges();
      this.electronService.on('inspect-element', () => { })
    });

    this.electronService.on('open-logs', () => {
      this.isLogsWindowVisible = true;
    })
  }

  selectedSignal: string | null = null;

  updateSignal(signal: string | null) {
    this.selectedSignal = signal;
  }

}
