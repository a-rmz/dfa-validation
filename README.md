# Do androids dream on validation tests?

Did you ever dreamed with testing your Deterministic Finite Automaton's validity? Well, you've come to the right place. Come and see!

### How does this look?
Just like this!

![Main window](https://github.com/a-rmz/dfa-validation/raw/master/screenshots/main_window.png)


### What do I need to run it?

#### Linux or MacOS
* `git clone https://github.com/a-rmz/dfa-validation.git` to download the repo
* `cd` into the directory where downloaded
* To install [Gtkmm](http://www.gtkmm.org/en/)
  * Linux: `sudo apt-get install libgtkmm-3.0-dev`
  * MacOS: Assuming you have [brew](https://brew.sh/) installed:
    * `brew update`
    * `brew install gtkmm3`
* `sudo chmod +x ./comp.sh` to make the compile file executable
* `./comp.sh` to run the compile command
* After compiled for the first time, you can now just run `./dfa_app` to run the app

#### Windows
So sorry about you guys...

