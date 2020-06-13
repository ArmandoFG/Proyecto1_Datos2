// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from 'vscode';
import * as path from 'path';

/**
 * 
 * @param context 
 */
var datos = (callback:any) => { } ;
var datosServer = (callbacl:any) => {}; 
var fs = require("fs");
const folderpath = "/home/armando/Project/src";
export function activate(context: vscode.ExtensionContext) {
	context.subscriptions.push(
		vscode.commands.registerCommand('catCoding.start', () => {
			CatCodingPanel.createOrShow(context.extensionPath);
		})
	);

	context.subscriptions.push(
		vscode.commands.registerCommand('catCoding.doRefactor', () => {
			if (CatCodingPanel.currentPanel) {
				CatCodingPanel.currentPanel.doRefactor();
			}
		})
	);

	if (vscode.window.registerWebviewPanelSerializer) {
		
		vscode.window.registerWebviewPanelSerializer(CatCodingPanel.viewType, {
			async deserializeWebviewPanel(webviewPanel: vscode.WebviewPanel, state: any) {
				console.log(`Got state: ${state}`);
				CatCodingPanel.revive(webviewPanel, context.extensionPath);
			}
		});
	}
}


class CatCodingPanel {
	
	public static currentPanel: CatCodingPanel | undefined;

	public static readonly viewType = 'catCoding';

	private readonly _panel: vscode.WebviewPanel;
	private readonly _extensionPath: string;
	private _disposables: vscode.Disposable[] = [];
/**
 * 
 * @param extensionPath 
 */
	public static createOrShow(extensionPath: string) {
		const column = vscode.window.activeTextEditor
			? vscode.window.activeTextEditor.viewColumn
			: undefined;

		
		if (CatCodingPanel.currentPanel) {
			CatCodingPanel.currentPanel._panel.reveal(column);
			return;
		}

		
		const panel = vscode.window.createWebviewPanel(
			CatCodingPanel.viewType,
			'Cat Coding',
			column || vscode.ViewColumn.One,
			{
				
				enableScripts: true,

				
				localResourceRoots: [vscode.Uri.file(path.join(extensionPath, 'media'))]
			}
		);

		CatCodingPanel.currentPanel = new CatCodingPanel(panel, extensionPath);
	}
/**
 * 
 * @param panel 
 * @param extensionPath 
 */
	public static revive(panel: vscode.WebviewPanel, extensionPath: string) {
		CatCodingPanel.currentPanel = new CatCodingPanel(panel, extensionPath);
	}
/**
 * 
 * @param panel 
 * @param extensionPath 
 */
	private constructor(panel: vscode.WebviewPanel, extensionPath: string) {
		this._panel = panel;
		this._extensionPath = extensionPath;

		
		this._update();

		
		this._panel.onDidDispose(() => this.dispose(), null, this._disposables);

		
		this._panel.onDidChangeViewState(
			e => {
				if (this._panel.visible) {
					this._update();
				}
			},
			null,
			this._disposables
		);

		
		this._panel.webview.onDidReceiveMessage(
			message => {
				switch (message.command) {
					case 'alert':
						vscode.window.showErrorMessage(message.text);
						return;
				}
			},
			null,
			this._disposables
		);
	}

	public doRefactor() {
		
		this._panel.webview.postMessage({ command: 'refactor' });
	}

	public dispose() {
		CatCodingPanel.currentPanel = undefined;

		
		this._panel.dispose();

		while (this._disposables.length) {
			const x = this._disposables.pop();
			if (x) {
				x.dispose();
			}
		}
	}

	public _update() {
		const webview = this._panel.webview;

				actualizar();
				this._updateForCat(webview);
				return;

			
		}
	
	
/**
 * 
 * @param webview 
 */
	private _updateForCat(webview: vscode.Webview) {
		this._panel.title = "HeapVisualizer";
		this._panel.webview.html = this._getHtmlForWebview(webview);
	}
	public _heapVisualizar(){
		
	}
/**
 * 
 * @param webview 
 */
	private _getHtmlForWebview(webview: vscode.Webview) {
		// Local path to main script run in the webview
		const scriptPathOnDisk = vscode.Uri.file(
			path.join(this._extensionPath, 'media', 'main.js')
		);

		// And the uri we use to load this script in the webview
		const scriptUri = webview.asWebviewUri(scriptPathOnDisk);

		
		return `<!DOCTYPE html>
		<html>
			<head>
				<meta name="viewport" content="width=device-width, initial-scale=1.0">
				<link rel="stylesheet" href="http://designer.igniteui.com/packages/bootstrap/bootstrap.min.css">
				<link rel="stylesheet" href="http://designer.igniteui.com/css/themes/infragistics/infragistics.theme.css">
				<link rel="stylesheet" href="http://designer.igniteui.com/css/structure/infragistics.css">
				<!--
					Update the Ignite UI script references to your licensed copies before deploying.
					Ignite UI License: http://www.infragistics.com/legal/license/ultimate/
				-->
				<script src="http://code.jquery.com/jquery-1.10.2.min.js"></script>
				<script src="http://code.jquery.com/ui/1.10.4/jquery-ui.min.js"></script>
				<script src="http://cdnjs.cloudflare.com/ajax/libs/modernizr/2.8.2/modernizr.min.js"></script>
				<script src="http://designer.igniteui.com/js/infragistics.core.js"></script>
				<script src="http://designer.igniteui.com/js/infragistics.lob.js"></script>
				<!-- You may remove the datasources.js script if you are not using Designer sample data. -->
				<script src="http://designer.igniteui.com/js/datasources.js"></script>
				<script id="code">
					$(document).ready(function () {
		
					});
				</script>
			</head>
			<body>
			<style type="text/css">
			document.getElementById("tablaCliente"), th, td{
				border: 4px solid teal;
				border-collapse: collapse;
				 top: -200px; 
				 right: 100px;

			}
			document.getElementById("tablaServer"), th, td{
				border: 4px solid teal;
				border-collapse: collapse;
				 top: -200px; 
				 right: 100px;
			}
			
			td{
				background-color: SILVER;
				color: black;
			}
			th{
				background-color: TEAL;
				color: black;
			}
			</style>
				<div id="row1" class="row">
					<div class="col-md-4">
					<p id="text2">Garbage Collector</p>
				</div>
					<div class="col-md-4">
					<p id="text3">Remote Memory</p>
				</div>
					<div class="col-md-4">
					</div>
				</div>
				<div id="row2" class="row">
					<div class="col-md-4">
					<ul id="listaGarbage"></li></ul>
				</div>
					<div class="col-md-4">
					<p id="text4">Direccion IP</p>
				</div>
					<div class="col-md-4">
		</div>
					<textarea id="textarea1"></textarea>
				</div>
				<div id="row3" class="row">
					<div class="col-md-4">
					<button onclick="mostrarHeapVisualizer()">Actualizar</button>
				</div>
					<div class="col-md-4">
					<p id="text5">Contraseña</p>
			</div>
					<div class="col-md-4">
		</div>
					<textarea id="textarea3"></textarea>
				</div>
				<div id="row4" class="row">
					<div class="col-md-4">
					</div>
					<div class="col-md-4">
					<p id="text6">Puerto</p>
				</div>
					<div class="col-md-4">
				</div>
					<textarea id="textarea3"></textarea>
				</div>
				<div id="row5" class="row">
					<div class="col-md-4">
					</div>
					<div class="col-md-4">
					<p id="text7">Nombre de la conexion</p>
				</div>
					<div class="col-md-4">
		</div>
					<textarea id="textarea4"></textarea>
				</div>
				<div id="row6" class="row">
					<div class="col-md-4">
					</div>
					<div class="col-md-4">
					<button onclick="conectarServidor()">Conectar</button>
				</div>
					<div class="col-md-4">
					</div>
				</div>
			<table id="tablaCliente">
			<table style="width: 50%;">
			<tr>
				<th>Tipo</th>
				<th>Direcciòn de memoria</th>
				<th>Lugar de almacenamiento</th>
				
			</tr>
			"${datos}"
		</table>
			<table id="tablaServer">
			<table style="width: 50%;">
			<tr>
				<th>Tipo</th>
				<th>Direcciòn de memoria</th>
				<th>Lugar de almacenamiento</th>
				
			</tr>
			"${datosServer}"	
		</table>

		
		
			</body>
		</html>`;
	}
}

function actualizar(){
	try {
		var data = fs.readFileSync(path.join(folderpath,'data.txt'), 'utf8');
		var dataS = fs.readFileSync(path.join(folderpath,'dataClienteServer.txt'), 'utf8');
		datos = data;
		datosServer = dataS;
	} catch(e) {
		console.log('Error:', e.stack);
	}
	
}
