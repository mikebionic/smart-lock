module.exports = (sequelize, type) => {
	return sequelize.define('Rp_acc_attendance',
	{
		RpAccAttId: {
			field: 'arap_att_id',
			type: type.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		RpAccId: {
			field: 'arap_id',
			type: type.INTEGER
		},
		// RpAccAttDate: {
		// 	field: 'arap_att_date',
		// 	type: type.DATETIME
		// }
	},
	{
		tableName: 'tbl_mg_arap_attandence',
		timestamps: false
	})
}