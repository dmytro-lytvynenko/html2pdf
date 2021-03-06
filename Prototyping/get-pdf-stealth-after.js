const puppeteer = require('puppeteer-extra');
const pluginStealth = require('puppeteer-extra-plugin-stealth')();
puppeteer.use(pluginStealth);

(async() => {
    const browser = await puppeteer.launch({headless:true, userDataDir: "./user_data"});
    const page = await browser.newPage();
    await page.goto('https://www.pragmaticlinux.com/2021/07/import-a-cmake-project-into-visual-studio-code/');
    await page.pdf({path: 'some.pdf'});
    browser.close();
})();
