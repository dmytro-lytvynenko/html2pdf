const puppeteer = require('puppeteer-extra');
const pluginStealth = require('puppeteer-extra-plugin-stealth')();
puppeteer.use(pluginStealth);

(async() => {
    const browser = await puppeteer.launch({headless:false, userDataDir: "./user_data"});
    const page = await browser.newPage();
    await page.goto('https://www.learncpp.com/');
})();
