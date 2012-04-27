<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="./html.dtd">

	<xsl:template match="titre"></xsl:template>

	<xsl:template match="auteur"></xsl:template>

	<xsl:template match="resume">
		<div class="alert alert-success">
			<a class="close" data-dismiss="alert">×</a>
			<h4 class="alert-heading">Résumé</h4>
		</div>
	</xsl:template>

	<xsl:template match="section">
			<h2>Section</h2>
	</xsl:template>

	<xsl:template match="p">
		<p style="text-align: justify;">Hello World !</p>
	</xsl:template>

</xsl:stylesheet> 
