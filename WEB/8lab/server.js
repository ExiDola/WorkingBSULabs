const express = require('express');
const path = require('path');

const __dirnameJS = path.resolve();

const mainApp = express();
const port = 3000;

mainApp.use(express.static(path.join(__dirnameJS, 'dist')));

mainApp.get('/', (req, res) => {
    res.sendFile(path.resolve(__dirnameJS, 'dist', 'index.html'));
});


mainApp.get('/phones.json', (req, res) => {
    const filePath = path.resolve(__dirnameJS, 'phones.json');
    res.download(filePath);
});

mainApp.listen(port, () => {
    console.log(`Сервер запущен на порту ${port}`);
});
