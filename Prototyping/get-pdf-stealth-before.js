const puppeteer = require('puppeteer-extra');
const pluginStealth = require('puppeteer-extra-plugin-stealth')();
puppeteer.use(pluginStealth);

(async() => {
    const browser = await puppeteer.launch({headless:false, userDataDir: "./user_data"});
    const page = await browser.newPage();
    //await page.setViewport({width: 800, height: 600});
    //await page.goto('https://stackoverflow.com/questions/tagged/c%2b%2b11');
    await page.goto('https://datadome.co/');
    // await page.pdf({path: 'some.pdf'});
    // browser.close();
})();
