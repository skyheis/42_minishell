
<h1 align="center">
	Duckshell
</h1>

<p align="center">
	<b><i>A simple shell for the "minishell" 42's project, named duckshell :D</i></b><br>
</p>
<p align="center">
	<img alt="Code size in bytes" src="https://img.shields.io/github/languages/code-size/skyheis/42_minishell" />
    <img alt="Contributors" src="https://img.shields.io/github/contributors/skyheis/42_minishell?color=orange" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/skyheis/42_minishell?label=C&style=plastic" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/skyheis/42_minishell?color=green" />
    <img alt="42 school" src="https://img.shields.io/badge/42-Florence-9cf" />
</p>


---

<h2 align="center">
	🦆 Map of the project
</h2>
<p align="center">
	<b><i>Thanks to <a href="https://github.com/marzianegro">@marzianegro</a> for prettifying my map :)</i></b><br>
</p>

<p align="center">
	<img src="https://github.com/skyheis/42_minishell/blob/main/duckmap.jpg" />

</p>

---

## 🐳 Installation or Docker usage

This shell uses 'readline', so the library has to be installed. For simple testing you can build the image with Docker.

To pull files
```bash
git clone git@github.com:skyheis/42_minishell.git
```
To compile the duckshell

```bash
$ make
```
To load just run the binary
```bash
$ ./minishell
```

You can download the image and run in docker with the following command

```bash
$ docker run -it --name duckshell --rm skyheis/duckshell:latest
```

Or you can build the image and run with the following commands

```bash
$ docker build -t duckshell .
$ docker run -it --name duckshell --rm duckshell
```

## ⚖️ License
See [LICENSE](LICENSE)
