import { ChangeDetectorRef, Component, inject } from '@angular/core';
import { SidebarComponent } from "../sidebar/sidebar.component";
import { FooterComponent } from "../footer/footer.component";
import { RouterOutlet } from '@angular/router';
import { ElectronService } from '../../services/electron.service';
import { ConfigureFileComponent } from '../configure-file/configure-file.component';

@Component({
  selector: 'app-layout',
  standalone: true,
  imports: [SidebarComponent, RouterOutlet, FooterComponent, ConfigureFileComponent],
  templateUrl: './layout.component.html',
  styleUrl: './layout.component.css'
})

export class LayoutComponent {

  isConfigureFileVisible: boolean = false;

  private electronService = inject(ElectronService);
  private cdr = inject(ChangeDetectorRef);

  ngOnInit(): void {
    this.electronService.on('open-configure-file', () => {
      this.isConfigureFileVisible = true;
      this.cdr.detectChanges();
      this.electronService.on('inspect-element', () => { })
    });
  }

  selectedSignal: string | null = null;

  updateSignal(signal: string | null) {
    this.selectedSignal = signal;
  }

  closeConfigurationFile() {
    this.isConfigureFileVisible = false;
    this.cdr.detectChanges();
  }

}
