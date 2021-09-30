"use strict"

const vscode = require('vscode')
const {
    convertToComment
} = require('./42-comment')

function ignore() {}

function transformToComment(editor) {
    const editOperations = editor.selections.map((selection) => {
        let last = editor.document.lineAt(selection.end.line).range.end.character
        selection = new (vscode.Selection)(
            selection.start.line,
            0,
            selection.end.line,
            last)
        let text = editor.document.getText(selection)
        text = convertToComment(text)

        return {
            text: text,
            selection: selection,
        }
    })
    editor.edit(builder => {
        editOperations.forEach(({
            text,
            selection
        }) => {
            builder.delete(selection)
            builder.insert(selection.anchor, text)
        })
    })
}

function activate(context) {
    context.subscriptions.push(vscode.commands.registerCommand('extension.42-comment', () => {
        let editor = vscode.window.activeTextEditor
        if (!editor) {
            return;
        }
        transformToComment(editor)
    }))
}

module.exports = {
    activate,
    deactivate: ignore
}