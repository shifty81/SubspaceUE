#!/bin/bash

# serve-docs.sh - Start local documentation server
# Usage: ./serve-docs.sh [port]

PORT=${1:-3000}
DOCS_DIR="docs"

echo "================================================"
echo " SubspaceUE Documentation Server"
echo "================================================"
echo ""
echo " Starting server on port $PORT..."
echo " Documentation will be available at:"
echo ""
echo "   http://localhost:$PORT"
echo ""
echo " Press Ctrl+C to stop the server"
echo "================================================"
echo ""

# Check if docs directory exists
if [ ! -d "$DOCS_DIR" ]; then
    echo "Error: docs directory not found!"
    echo "Make sure you run this script from the project root."
    exit 1
fi

cd "$DOCS_DIR" || exit 1

# Try Python 3 first, then Python 2, then fail
if command -v python3 &> /dev/null; then
    python3 -m http.server "$PORT"
elif command -v python &> /dev/null; then
    python -m SimpleHTTPServer "$PORT"
else
    echo "Error: Python not found!"
    echo "Please install Python 3 to use this script."
    echo ""
    echo "Alternatives:"
    echo "  - Install Python: https://python.org/"
    echo "  - Use Node.js: npm install -g http-server && http-server -p $PORT"
    echo "  - Use PHP: php -S localhost:$PORT"
    exit 1
fi
