# ProtoIndigo Interpreter

A small programming language project currently in testing and active development.

ProtoIndigo v1.0.1

## Current Features

- Variable declaration
- Constants declaration
- Function declaration
- Typing
- Basic syntax parsing
- Syntax error reporting
- Undefined identifier error reporting

## Supported Types

- **Boolean:** `true` / `false`
- **String:** `"helloworld"`
- **Integer:** Whole numbers

## Simple Example

```bre
	proto "Hello World!";
	new name = "ProtoIndigo";

	proto name;
```

## Advanced Example

```bre
	new name = "xFoxyyy";
	new is_Developer = true;

	new #string description = "This is my first time using the ProtoIndigo!";

	new const age = 100;
	new const #number a = 3;

	new f(a, b) {
	
	};

	new const footer = "Bruh, I can't create functions in ProtoIndigo yet...";

	proto name;
	proto "Hello World by ProtoIndigo!";

	proto age;
```

## Testing

You can clone this repository and compile it yourself, or use the pre-built executable via your CLI.
[Download the executable here!](https://github.com/ipxzfoxy/protoindigo/blob/main/indigo.exe)

### Using the CLI:

```powershell
	./indigo.exe index.bre
```

* The first argument must be the path to the file you want to interpret.

## Notes

- The parser may terminate the process if it encounters any syntax errors.
- Function declaration is supported by the parser, but functions cannot yet execute code inside their scope or be called.

## Developer

Developed by **Victor Botelho Anunciação** (xFoxyyy0).
