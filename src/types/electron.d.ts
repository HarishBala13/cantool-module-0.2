declare namespace NodeJS {
    interface Global {
        electron: {
            openFile: () => Promise<string[]>;
        }
    }
}