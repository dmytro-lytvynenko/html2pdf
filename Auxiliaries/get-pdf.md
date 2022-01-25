# Puppeteer: High-Level API to Control Chrome or Chromium



## Puppeteer is a Node library that provides a high-level API to control Chrome or Chromium

By default, [puppeteer](https://github.com/puppeteer/puppeteer) runs headless and allows us to do automation. During the installation, it downloads a recent version of Chromium that is guaranteed to work with the API:

```
$ npm i puppeteer
```

To work with Puppeteer, let's use our JavaScript code (get-pdf.js file):

```
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
```

In a nutshell, this script loads the puppeteer module, making it accessible in the puppeteer variable. Next, it defines a timeout function to get a delay.

Then, it asynchronously launches the browser with a window of the specified size, opens the given URL, waits 10 seconds, and finally create pdf file and closes the browser.

For detailed information, we can consult the [Puppeteer API](https://github.com/puppeteer/puppeteer/blob/main/docs/api.md).

Let’s try it out:

```
$ node get-pdf.js
```
