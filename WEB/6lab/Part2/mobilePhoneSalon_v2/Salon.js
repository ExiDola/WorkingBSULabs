class TLocalStorage {
    constructor() {}

    setValue(key, value) {
        localStorage.setItem(key, value);
    }

    getValue(key) {
        return localStorage.getItem(key);
    }

    deleteValue(key) {
        localStorage.removeItem(key);
    }

    getAllKeys() {
        return Object.keys(localStorage);
    }
}

const storage = new TLocalStorage();

function AddValue() {
    var key = prompt("Введите название объекта:");
    var value = prompt("Введите описание объекта:");
    
    if (key && value) {
        if (storage.getValue(key) === null) {
            storage.setValue(key, value);
            updateDisplay();
        } else {
            displayError("Такой ключ уже существует!");
        }
    } else {
        displayError("Введите корректные данные!");
    }
}

function DeleteValue() {
    var key = prompt("Введите название объекта:");
    
    if (storage.getValue(key) !== null) {
        storage.deleteValue(key);
        updateDisplay();
    } else {
        displayError("Нет такого ключа!");
    }
}

function GetValueInfo() {
    var key = prompt("Введите название объекта:");
    
    var value = storage.getValue(key);
    
    if (value !== null) {
        displayInfo(key + " - " + value);
    } else {
        displayError("Нет информации для ключа: " + key);
    }
}

function ListValues() {
    var keys = storage.getAllKeys();   
    
    if (keys.length === 0) {
        displayInfo("Хранилище пусто");
    } else {
        var allInfo = keys.map(key => key + " - " + storage.getValue(key)).join("<br>");
        displayInfo(allInfo);
    }
}

function updateDisplay() {
    ListValues(); 
}

function displayInfo(message) {
    var displayDiv = document.getElementById("display");
    displayDiv.innerHTML = message;
}

function displayError(message) {
    var displayDiv = document.getElementById("display");
    displayDiv.textContent = message;
}

window.onload = function() {
    updateDisplay();
};
