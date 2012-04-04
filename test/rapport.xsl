<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="/">
		<html>
			<head>
				<meta charset="utf-8" />
				<link rel="stylesheet" type="text/css" href="./bootstrap.css" />
				<link rel="stylesheet" type="text/css" href="./bootstrap-responsive.css" />
				<script type="text/javascript" href="./bootstrap.css" />
				<title>Lib'If - Documents</title>
			</head>
			<body>
				<div class="page-header">
					<h1>
						<xsl:value-of select="./titre"/>
						<small><xsl:value-of select="./auteur/prenom"/> <xsl:value-of select="./auteur/nom"/></small>
					</h1>
				</div>
				<div class="row">
					<xsl:apply-templates />
				</div>
			</body>
		</html>
	</xsl:template>

	<xsl:template match="resume">
		<div class="span3 column">
			<div class="alert alert-info">
				<a class="close" data-dismiss="alert">×</a>
				<h4 class="alert-heading">Résumé</h4>
				<xsl:value-of select="."/>
			</div>
		</div>
	</xsl:template>

	<xsl:template match="section">
		<div class="span9 column">
			<h2><xsl:value-of select="@titre"/></h2>
			<xsl:apply-templates />
		</div>
	</xsl:template>

	<xsl:template match="p">
		<p style="text-align: justify;">
			<xsl:value-of select="."/>
		</p>
	</xsl:template>

</xsl:stylesheet> 