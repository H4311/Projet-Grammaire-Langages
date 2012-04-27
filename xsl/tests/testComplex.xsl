<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

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
				<xsl:apply-templates />
			</body>
		</html>
	</xsl:template>

	<xsl:template match="titre"></xsl:template>

	<xsl:template match="auteur"></xsl:template>

	<xsl:template match="resume">
		<div class="alert alert-success">
			<a class="close" data-dismiss="alert">×</a>
			<h4 class="alert-heading">Résumé</h4>
		</div>
	</xsl:template>

	<xsl:template match="section">
			<h2>@titre</h2>
			<xsl:apply-templates />
	</xsl:template>

	<xsl:template match="p">
		<p style="text-align: justify;">
			<xsl:apply-templates />
		</p>
	</xsl:template>

	<xsl:template match="img">
		<img>
			<xsl:attribute name="src">./@src</xsl:attribute>
			<xsl:attribute name="title">@title</xsl:attribute>
		</img>
	</xsl:template>

</xsl:stylesheet> 
