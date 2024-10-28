import { Routes } from '@angular/router';
import { LogsComponent } from './shared/logs/logs.component';
import { NetworkWindowComponent } from './shared/network-window/network-window.component';
import { SignalDetailsComponent } from './shared/signal-details/signal-details.component';
import { LayoutComponent } from './shared/layout/layout.component';
import { ConfigureFileComponent } from './shared/configure-file/configure-file.component';

export const routes: Routes = [
    {
        path: 'logs',
        component: LogsComponent,
        title: 'Logs'
    },
    {
        path: '',
        component: LayoutComponent,
        children: [
            {
                path: '',
                component: NetworkWindowComponent
            },
            {
                path: 'signal/:id',
                component: SignalDetailsComponent
            },
            {
                path: 'configure-file',
                component: ConfigureFileComponent
            }
        ]
    }
];
