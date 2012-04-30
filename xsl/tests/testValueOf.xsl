<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="./tests/html.dtd">

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
						<xsl:value-of select="./titre"/> - 
						<small><xsl:value-of select="./auteur/prenom"/>&#32; <xsl:value-of select="./auteur/nom"/></small>
					</h1>
				</div>
				<p> Blablabla </p>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet> 
