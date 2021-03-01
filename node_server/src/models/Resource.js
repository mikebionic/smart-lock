module.exports = (sequelize, type) => {
	return sequelize.define('Resource',
	{
		ResId: {
			type: type.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		ResName: type.STRING
	},
	{
		tableName: 'tbl_dk_resource',
		timestamps: false
	})
}