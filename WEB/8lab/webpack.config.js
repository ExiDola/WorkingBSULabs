const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
    mode: 'development',
    entry: './src/index.js', // Убедитесь, что файл index.js находится в src
    output: {
        filename: 'main.js', // Имя выходного файла
        path: path.resolve(__dirname, 'dist'), // Путь для сохранения собранных файлов
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: './src/template.html', // Убедитесь, что ваш шаблон находится в src
        }),
    ],
    resolve: {
        extensions: ['.js'], // Расширения файлов для обработки
        // Если у вас есть псевдонимы путей, настройте их здесь
        alias: {
            //...
        }
    }
};
