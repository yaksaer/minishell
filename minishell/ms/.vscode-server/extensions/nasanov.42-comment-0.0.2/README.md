# 42-style block comments

## Features

``` c
int     main()
{
    return 0;
}
```
turns into:

``` c
/*
** int     main()
** {
**     return 0;
** }
*/
```

## Usage
Select the text that you want to transform, then call the command bar with:

`Ctrl+Shift+P` or `shift+cmd+*` on MAC, `ctrl+alt+*` on Windows/Linux,

And run the command:

`> 42-comment`

## Keybindings
You can bind these commands to another shortcut by adding something like this to your `keybindings.json`:
```
{ "key": "shift+cmd+*", "command": "extension.42-comment", "when": "editorTextFocus"}
```
or go to Preferences -> Keyboard Shortcuts, find 42-comment, change a shortcut

## Known Issues

Some known issues should be here.

## Release Notes

Users appreciate release notes as you update your extension.

### 0.0.1

Initial release of 42-comment

### 0.0.2

Keybindings were added
