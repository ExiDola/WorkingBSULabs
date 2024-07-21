const path = require('path');

module.exports = {
  entry: {
    gettingStarted: './gettingStarted.jsx',
    p2: './p2.jsx', // Дополнительный пример входной точки
  },
  module: {
    rules: [
      {
        test: /\.(js|jsx)$/,
        exclude: /node_modules/,
        use: 'babel-loader',
      },
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader'],
      },
      {
        test: /\.(png|jpg|gif)$/,
        use: [
          {
            loader: 'url-loader',
            options: {
              limit: 8192,
            },
          },
        ],
      },
    ],
  },
  resolve: {
    extensions: ['*', '.js', '.jsx'],
  },
  output: {
    path: path.resolve(__dirname, 'compiled'),
    publicPath: '/',
    filename: '[name].bundle.js',
  },
  mode: 'development',
  devServer: {
    contentBase: path.join(__dirname, 'public'),
    compress: true,
    port: 3030,
    open: true,
  },
};
