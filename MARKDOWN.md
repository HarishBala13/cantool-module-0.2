# Project version 0.0.0
    Handled by @Harish B

# Developed an Angular project with Electron as a tool to convert the Web application into a Desktop App.
# Settled up basic environments in this project.

# NPM Commands - To be installed precisely in the specific folders to avoid conflicts

root/
    npm init -y  ==> Initializing the node in project
    npm install electron --save-dev ==> Installing and adding electron to this project

./
    npm install --save-dev @electron-forge/cli  ==> Installing and adding electron-forge cli to this project.
    npm exec --package=@electron-forge/cli -c "electron-forge import" ==> Installing and adding @electron-forge/maker-deb @electron-forge/maker-rpm @electron-forge/maker-squirrel @electron-forge/maker-zip @electron-forge/plugin-auto-unpack-natives @electron-forge/plugin-fuses @electron/fuses to this project.

# Publishing and Distributing
    To publish this use npm run make from the package.json to publish and distribute to a client.
    Before publishing make to sure to check few things:-
        * Add author & description in forge.config.js which will added after executing this command npm exec --package=@electron-forge/cli -c "electron-forge import" 
            Ex:- makers: [
                            {
                                name: '@electron-forge/maker-squirrel',
                                config: {
                                    authors: "Harish B",
                                    description: "Buidling an tool that can collobrate with the embedded systems with serialport and more signals with Angular as a front-end framework in a Desktop application."
                                },
                            },...
                        ]
        * Add if(require('electron-squirrel-startup')) app.quit(); in main.js

# learned
