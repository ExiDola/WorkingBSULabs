import express from 'express';
import path, { dirname } from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const mainApp = express();
const port = 3000; 

mainApp.use(express.static(path.join(__dirname, 'static')));

// Определяем маршрут для отдачи страницы index.html
mainApp.get('/', (req, res) => {
    res.sendFile(path.resolve(__dirname, 'static', 'index.html'));
});

mainApp.get('/second.html', (req, res) => {
    res.sendFile(path.resolve(__dirname, 'static', 'second.html'));
});

// Определяем маршрут для скачивания файла phones.json
mainApp.get('/phones.json', (req, res) => {
    const filePath = path.join(__dirname, 'phones.json');
    res.download(filePath);
});

// Запускаем сервер
mainApp.listen(port, () => {
    console.log(`Сервер запущен на порту ${port}`);
});
