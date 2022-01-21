# html2pdf



## Purpose

html2pdf's purpose is to convert Web-based manuals to PDF for enabling full-text search.

html2pdf is an intellectual tool that can significantly reduce the time spent searching for information in web-books and web-manuals.

## Minimum viable product

html2pdf is a console application.

html2pdf should get the table of contents from the [https://www.learncpp.com/](https://www.learncpp.com/) home page and put it into learncpp.pdf, where all positions of the content are links to the relevant pages of the site.

## Algorithm for obtaining the Minimum viable product

1. Get the home page of the https://www.learncpp.com/
2. Select content related to the subject of the site.
3. Pick out the table of contents.
4. Put selected content to the learncpp.pdf

## Build & run html2pdf

### On a local Linux machine

To build the project on a local Ubuntu run `build_script` on the root directory of the project:

`$ sudo ./build_script.sh`

After the successful project's build, run on the root directory of the project:

`$ cd html2pdf/`
`$ ./html2pdf`

### On a docker container

Build docker image of the project on the root directory of the project:

`$ docker build . --tag ubuntu-html2pdf-cicd-v0`

Create container for building project

`$ docker create -it ubuntu-html2pdf-cicd-v0`

Start container

`$ docker start -ai CONTAINER_NAME`

In other linux terminal run next command from the root of the project:

`$ docker cp . CONTAINER_NAME:/home/html2pdf/`

In the container terminal run command:

`# sudo ./build_script.sh`

Run html2pdf

`# cd html2pdf/`
`# ./html2pdf`
