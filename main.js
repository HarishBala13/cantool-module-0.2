const { app, BrowserWindow, Menu, ipcMain, dialog } = require('electron');
const fs = require('fs');
const path = require('path');
if (require('electron-squirrel-startup')) app.quit();

let mainWindow;
let logsWindow;
let windows = [];
const logMessages = [];
let index = 0;

const mainMenuTemplate = [
    {
        label: 'File',
        submenu: [
            {
                label: 'Configure',
                click: () => {
                    mainWindow.webContents.send('open-configure-file');
                }
            },
            {
                label: 'Save',
                click() {
                    console.log('File saved');
                }
            },
            {
                label: 'Close',
                click() {
                    console.log('File closed');
                }
            },
        ]
    },
    {
        label: 'Edit',
        submenu: [
            {
                label: 'Cut',
                click() {
                    console.log('text cut');
                }
            },
            {
                label: 'Copy',
                click() {
                    console.log('text copied');
                }
            },
            {
                label: 'Paste',
                click() {
                    console.log('text pasted');
                }
            },
        ]
    },
    {
        label: 'Inspect',
        accelerator: 'Ctrl+Shift+I',
        click: () => {
            mainWindow.webContents.openDevTools();
            mainWindow.webContents.send('inspect-element');
        }
    },
    {
        label: 'Quit',
        click() {
            app.quit();
        }
    },
    {
        label: 'Open Logs',
        click: () => {
            createLogsWindow();
        }
    },
    // {
    //     label: 'Reload',
    //     accelerator: 'Cmd+Ctrl+R',
    //     click: () => {
    //         const focusedWindow = BrowserWindow.getFocusedWindow();
    //         if (focusedWindow) {
    //             focusedWindow.reload();
    //         } else {
    //             console.log("Reload is disabled in this state.");
    //         }
    //     }
    // }
];

const childMenuTemplate = [
    {
        label: 'Save',
        click() {
            console.log('File saved');
        }
    },
    {
        label: 'Inspect',
        accelerator: 'Ctrl+Shift+I',
        click: () => {
            logsWindow.webContents.openDevTools();
            logsWindow.webContents.send('inspect-element');
        }
    },
    {
        label: 'Quit',
        click() {
            if (logsWindow) logsWindow.close();
            else app.quit();
        }
    },
    // {
    //     label: 'Reload',
    //     accelerator: 'CmdOrCtrl+R',
    //     click: () => {
    //         const focusedWindow = BrowserWindow.getFocusedWindow();
    //         if (focusedWindow) {
    //             focusedWindow.reload();
    //         } else {
    //             console.log("Reload is disabled in this state.");
    //         }
    //     }
    // }
];

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: false,
            preload: path.join(__dirname, 'preload.js')
        }
    });

    mainWindow.loadURL(path.join(__dirname, 'dist/angular-app/browser/index.html'));

    windows.push(mainWindow);

    const menu = Menu.buildFromTemplate(mainMenuTemplate);
    Menu.setApplicationMenu(menu);

    mainWindow.on('closed', () => {
        windows = windows.filter(_window => _window != mainWindow);
    });
}

function createLogsWindow() {
    logsWindow = new BrowserWindow({
        x: 0,
        y: 650,
        width: 1200,
        height: 200,
        parent: mainWindow,
        title: 'Logs Window',
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: false,
            preload: path.join(__dirname, 'preload.js')
        }
    });

    const childMenu = Menu.buildFromTemplate(childMenuTemplate);
    logsWindow.setMenu(childMenu);

    logsWindow.webContents.on('did-finish-load', () => {
        logsWindow.webContents.send('navigate-to-logs');
    });

    windows.push(logsWindow);

    if (process.env.NODE_ENV === 'development') {
        logsWindow.loadURL('http://localhost:4200/logs');
    } else {
        logsWindow.loadURL(path.join(__dirname, 'dist/angular-app/browser/index.html'));
    }

    logsWindow.on('closed', () => {
        windows = windows.filter(_window => _window != logsWindow);
    });
}

function emitLog(message) {
    logMessages.push(message);
    if (logsWindow) {
        logsWindow.webContents.send('update-logs', logMessages[index++]);
    }
}

ipcMain.on('new-log', (event, log) => {
    logMessages.push(log);
    if (logsWindow) {
        logsWindow.webContents.send('update-logs', logMessages);
    }
});

ipcMain.on('clear-logs', () => {
    logMessages.length = 0;
    if (logsWindow) {
        logsWindow.webContents.send('update-logs', logMessages);
    }
});

ipcMain.on('save-code', (event, configureArray) => {
    const options = {
        title: 'Configure Code',
        defaultPath: path.join(__dirname, `${configureArray[1]}`),
        buttonLabel: 'Save',
        filters: [
            { name: 'C Files', extensions: ['c'] },
        ],
        message:'Create a C Configure file to communicate with your board'
    };

    dialog.showSaveDialog(null, options).then((file) => {
        if (!file.canceled) {
            fs.writeFile(file.filePath.toString(), configureArray[0], (err) => {
                if (err) {
                    emitLog(err.message.toString());
                } else {
                    const logMessage = `Log entry at ${new Date().toLocaleTimeString()} and ` + `File has been saved to ${file.filePath}`;
                    emitLog(logMessage);
                }
            });
        }
    }).catch(err => {
        emitLog(err);
    });
});

ipcMain.on('new-log', (event, log) => {
    logMessages.push(log);
    if (mainWindow) {
        mainWindow.webContents.send('update-logs', logMessages);
    }
});

ipcMain.on('clear-logs', () => {
    logMessages.length = 0;
    if (mainWindow) {
        mainWindow.webContents.send('update-logs', logMessages);
    }
});

app.on('ready', createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow();
    }
});


// click() {
//     dialog.showMessageBox(mainWindow, {
//         title: 'Form', message: 'Opened a form' // it's just opening a normal box
//     })
// }