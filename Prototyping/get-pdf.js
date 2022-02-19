const puppeteer = require('puppeteer');

function timeout(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
};

(async() => {
    const browser = await puppeteer.launch();
    const page = await browser.newPage();
    //await page.setViewport({width: 800, height: 600})
    //await page.goto('https://stackoverflow.com/questions/tagged/c%2b%2b11');
    await page.goto('https://datadome.co/');
    await timeout(1000)
    await page.pdf({path: 'some.pdf'});
    browser.close();
})();
