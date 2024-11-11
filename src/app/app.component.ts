import { ChangeDetectorRef, Component, inject, OnInit } from '@angular/core';
import { Router, RouterOutlet } from '@angular/router';
import { ElectronService } from './services/electron.service';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})

export class AppComponent implements OnInit {
  title = 'angular-app';

  private router = inject(Router);
  private electronService = inject(ElectronService);
  private cdr = inject(ChangeDetectorRef);

  ngOnInit(): void {
    this.electronService.on('navigate-to-logs', () => {
      this.router.navigate(['/logs']);
    });
    this.cdr.detectChanges();
  }
}
