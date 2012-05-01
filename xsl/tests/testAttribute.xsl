<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="./html.dtd">

	<xsl:template match="rapport">
		<html>
			<head>
				<meta charset="utf-8" />
				<link rel="stylesheet" type="text/css" href="./bootstrap/css/bootstrap.css" />
				<link rel="stylesheet" type="text/css" href="./bootstrap/css/bootstrap-responsive.css" />
				<script type="text/javascript" href="./bootstrap/js/bootstrap.js" />
				<title>Lib'If - Documents</title>
			</head>
			<body>
				<div class="page-header">
					<h1>
						Titre - 
						<small>Coucou</small>
					</h1>
				</div>
				<img>
					<xsl:attribute name="src">http://google.fr/img</xsl:attribute>
					<xsl:attribute name="title">Test !</xsl:attribute>
				</img>
				<p>Ce document est valide si l'element img ci-dessus contient deux attributs, src et title, avec une valeur donnee.</p>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet> 
