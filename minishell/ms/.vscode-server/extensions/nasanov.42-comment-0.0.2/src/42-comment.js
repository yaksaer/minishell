"use strict"

function convertToComment(text) {
    let lines = text.split(/\n/).map(s => s.replace(/\s*$/, ""))

    const firstLine = "/*\n"
    const middleLine = lines.map((str) => {
            const left = "** "
            const right = "\n"
            return left + str + right;
        }).join("")
    const lastLine = "*/"
    const result = firstLine + middleLine + lastLine

    return result;
}

module.exports = {
    convertToComment
}
