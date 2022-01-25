const puppeteer = require('puppeteer');

function timeout(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
};

(async() => {
    const browser = await puppeteer.launch();
    const page = await browser.newPage();
    await page.setViewport({width: 800, height: 600})
    await page.goto('https://habr.com/ru/company/otus/blog/575964/comments/');
    await timeout(10000)
    await page.pdf({path: 'some.pdf'});
    browser.close();
})();
