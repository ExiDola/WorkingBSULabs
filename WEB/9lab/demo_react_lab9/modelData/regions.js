"use strict";

/*
 * Load the model data for Lab9. We load into the property
 * lab9models.regionsModel a function that returns an array of strings with the
 * names of the phone models.
 */

var lab9models;

if (lab9models === undefined) {
  lab9models = {};
}

lab9models.regionsModel = function () {
  return [
    "iPhone 13",
    "iPhone 12",
    "Samsung Galaxy S21",
    "Samsung Galaxy S20",
    "Google Pixel 6",
    "Google Pixel 5",
    "OnePlus 9",
    "OnePlus 8",
    "Xiaomi Mi 11",
    "Xiaomi Mi 10",
    "Sony Xperia 1 III",
    "Sony Xperia 5 II",
    "Huawei P40",
    "Huawei P30",
  ];
};
