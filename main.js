const { app, BrowserWindow, Menu, ipcMain, dialog } = require('electron');
const fs = require('fs');
const path = require('path');

if (require('electron-squirrel-startup')) app.quit();

let mainWindow;
let logsWindow;
const logMessages = [];
let index = 0;

const mainMenuTemplate = [
    {
        label: 'File',
        submenu: [
            {
                label: 'Configure',
                // click() {
                //     dialog.showMessageBox(mainWindow, {
                //         title: 'Form', message: 'Opened a form' // it's just opening a normal box
                //     })
                // }
                click: () => {
                    mainWindow.webContents.send('open-form');
                }
            },
            {
                label: 'Save',
                click() {
                    console.log('File saved')
                }
            },
            {
                label: 'Close',
                click() {
                    console.log('File closed')
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
                    console.log('text cutted')
                }
            },
            {
                label: 'Copy',
                click() {
                    console.log('text copied')
                }
            },
            {
                label: 'Paste',
                click() {
                    console.log('text pasted')
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
            logsWindow.webContents.send('open-logs');
        }
    },
    {
        label: 'Reload',
        accelerator: 'Cmd+Ctrl+R',
        role: 'reload',
        click: (menuItem, focusedWindow) => {
            if (focusedWindow) {
                focusedWindow.reload();
            } else {
                console.log("Reload is disabled in this state.");
            }
        }
    }
];

const childMenuTemplate = [
    {
        label: 'Save',
        click() {
            console.log('File saved')
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
    {
        label: 'Reload',
        accelerator: 'Cmd+Ctrl+R',
        role: 'reload',
        click: (menuItem, focusedWindow) => {
            if (focusedWindow) {
                focusedWindow.reload();
            } else {
                console.log("Reload is disabled in this state.");
            }
        }
    }
];

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 800,
        height: 600,
        fullscreen: true,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: false,
            preload: path.join(__dirname, 'preload.js')
        }
    });

    // mainWindow.loadFile('dist/angular-app/browser/index.html');
    mainWindow.loadURL('http://localhost:4200');

    const menu = Menu.buildFromTemplate(mainMenuTemplate);
    Menu.setApplicationMenu(menu);
}

function createLogsWindow() {
    logsWindow = new BrowserWindow({
        x: 0,
        y: 650,
        width: 1200,
        height: 200,
        parent: mainWindow,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: false,
            preload: path.join(__dirname, 'preload.js')
        }
    });

    logsWindow.on('closed', () => {
        logsWindow = null;
    });

    const childMenu = Menu.buildFromTemplate(childMenuTemplate);
    logsWindow.setMenu(childMenu);

    logsWindow.webContents.on('did-finish-load', () => {
        logsWindow.webContents.send('navigate-to-logs');
    });

    logsWindow.loadURL('http://localhost:4200/logs');
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

ipcMain.on('save-code', (event, code) => {
    const options = {
        title: 'Save Code',
        defaultPath: path.join(__dirname, 'code.c'),
        buttonLabel: 'Save',
        filters: [
            { name: 'C Files', extensions: ['c'] },
        ],
    };

    dialog.showSaveDialog(null, options).then((file) => {
        if (!file.canceled) {
            fs.writeFile(file.filePath.toString(), code, (err) => {
                if (err) {
                    emitLog(err.message.toString());
                } else {
                    const successMessage = `Log entry at ${new Date().toLocaleTimeString()} and ` + `File has been saved to ${file.filePath}`;
                    emitLog(successMessage);
                }
                console.log(`File has been saved to your directory successfully`);
            });
        }
    }).catch(err => {
        console.log(err);
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

// ipcMain.handle('dialog:openFile', async () => {
//     const result = await dialog.showOpenDialog(mainWindow, {
//         properties: ['openFile']
//     });
//     return result.filePaths;
// });