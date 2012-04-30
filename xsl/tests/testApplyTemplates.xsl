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
						Titre - Prenom et Nom
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
			<h4 class="alert-heading">Resume</h4>
			<p> Blabla </p>
		</div>
	</xsl:template>

	<xsl:template match="section">
			<h2>Section titre</h2>
			<xsl:apply-templates />
	</xsl:template>

	<xsl:template match="p">
		<p style="text-align: justify;">
			<p> Bla bla
			<xsl:apply-templates />
			</p>
		</p>
	</xsl:template>

	<xsl:template match="img">
		<small>Image</small>
	</xsl:template>

</xsl:stylesheet> 
