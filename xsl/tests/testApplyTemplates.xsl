<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="./tests/html.dtd">

	<xsl:template match="p">
		<p style="text-align: justify;">
			<xsl:apply-templates />
		</p>
	</xsl:template>

</xsl:stylesheet> 
